#include "UserSystem.h"

void UserSystem::resizeUsers(SupermarketSystem& system, unsigned newCap)
{
	User** newUsers = new User * [newCap] {};

	for (size_t i = 0; i < system.userCount; i++)
	{
		newUsers[i] = system.users[i];
	}

	delete[] system.users;
	system.users = newUsers;

	system.userCapacity = newCap;
}

int  UserSystem::findUserIndex(SupermarketSystem& system, unsigned id)
{
	for (size_t i = 0; i < system.userCount; i++)
	{
		if (system.users[i]->getId() == id)
		{
			return i;
		}
	}
	return -1;
}

void UserSystem::login(SupermarketSystem& system, unsigned id, const MyString& password)
{

	if (system.currentUser)
	{
		std::cout << "You are already logged in another account" << std::endl;
		return;
	}
	
	for (size_t i = 0; i < system.userCount; i++)
	{
		if (!system.users[i])
		{ 
			continue;
		}

		if (id == system.users[i]->getId() && password == system.users[i]->getPass())
		{
			system.currentUser = system.users[i];
			std::cout << "User " << system.currentUser->getFullName().c_str()
				<< " with ID: " << system.currentUser->getId()
				<< " has been logged into the system!" << std::endl;
			return;
		}
	}

	std::cout << "Incorrect id/password!" << std::endl;
}

void UserSystem::logout(SupermarketSystem& system)
{
	system.currentUser = nullptr;
	std::cout << "You have logged out" << std::endl;
}

void UserSystem::leave(SupermarketSystem& system)
{
	if (!system.currentUser)
	{
		std::cout << "You have to log in to use this command";
	}

	unsigned userIndex = findUserIndex(system, system.currentUser->getId());
	delete system.users[userIndex];
	for (size_t i = userIndex; i < system.userCount - 1; i++)
	{
		system.users[i] = system.users[i + 1];
	}
	system.userCount--;
	std::cout << "Successfuly left." << std::endl;
	FeedSystem::addFeed(system, system.currentUser->getFullName(), "has left.");
	system.currentUser = nullptr;
}

void UserSystem::registerUser(SupermarketSystem& system, const MyString& role, const MyString& fn, const MyString& ln,
	const MyString& phone, unsigned age, const MyString& pass)
{
	User* newUser = nullptr;
	if (role == "manager")
	{
		newUser = new Manager(MyString(fn), MyString(ln), MyString(phone), age, MyString(pass));
		
		if (system.userCount >= system.userCapacity)
		{
			resizeUsers(system, system.userCount * 2);
		}
		system.users[system.userCount++] = newUser;
		std::cout << "Manager registered successfully!" << std::endl;

		Manager* manager = dynamic_cast<Manager*>(newUser);
		std::cout << "Special code: " << manager->getSpecialCode().c_str() << std::endl;

		MyString fileName = MyString(MyString::to_string(manager->getId())) + "_special_code.txt";
		std::cout << "Code: " << fileName.c_str() << std::endl;
		FeedSystem::addFeed(system, newUser->getFullName(), "Registered as a manager.");
	}
	else if (role == "cashier")
	{
		newUser = new Cashier(MyString(fn), MyString(ln), MyString(phone), age, MyString(pass));

		if (system.userCount >= system.userCapacity)
		{
			resizeUsers(system, system.userCount * 2);
		}
		system.users[system.userCount++] = newUser;

		std::cout << "Cashier registration pending approval from a manager." << std::endl;
		FeedSystem::addFeed(system, newUser->getFullName(), "Registered as a cashier and waits for approval.");
	}
	else
	{
		std::cout << "Invalid role" << std::endl;
		return;
	}
}

void UserSystem::listUserData(const SupermarketSystem& system)
{
	if (!system.currentUser)
	{
		std::cout << "Log in to have access to this function" << std::endl;
		return;
	}

	system.currentUser->printInfo();
}

void UserSystem::listWorkers(const SupermarketSystem& system)
{
	if (!system.currentUser)
	{
		std::cout << "Log in to have access to this function" << std::endl;
		return;
	}
	for (size_t i = 0; i < system.userCount; i++)
	{
		if (system.users[i]->getRole() == "cashier" || system.users[i]->getRole() == "manager")
		{
			system.users[i]->printInfo();
		}
		std::cout << "------------" << std::endl;
	}
}

void UserSystem::loadUsersFromFile(SupermarketSystem& system, const MyString& fileName)
{
	if (fileName == "")
	{
		std::cout << "Save file for users.txt corrupted or missing" << std::endl;
		return;
	}

	std::ifstream ifs(fileName.c_str());
	if (!ifs.is_open())
	{
		std::cout << "Cannot open users.txt" << std::endl;
		return;
	}

	MyString role, fn, ln, phone, pass;
	unsigned age;
	int approved;

	while (ifs >> role >> fn >> ln >> phone >> age >> pass >> approved)
	{
		if (ifs.fail())
		{
			ifs.clear();
			char buff[Constants::MAX_BUFFER_SIZE];
			std::cin.getline(buff, Constants::MAX_BUFFER_SIZE);
			continue;
		}

		if (system.userCount >= system.userCapacity)
		{
			resizeUsers(system, system.userCount * 2);
		}

		if (role == "manager")
		{
			system.users[system.userCount++] = new Manager(fn, ln, phone, age, pass);
		}
		else if (role == "cashier")
		{
			Cashier* cashier = new Cashier(fn, ln, phone, age, pass);
			if (approved)
			{
				cashier->setApproval();
			}
			system.users[system.userCount++] = cashier;
		}
	}
	ifs.close();
}

void UserSystem::saveUsers(const SupermarketSystem& system, const MyString& fileName)
{

	if (fileName == "")
	{
		std::cout << "Save file for users.txt corrupted or missing" << std::endl;
		return;
	}

	std::ofstream ofs(fileName.c_str());
	if (!ofs.is_open())
	{
		std::cout << "Cannot open users.txt" << std::endl;
		return;
	}

	for (size_t i = 0; i < system.userCount; i++)
	{
		if (Manager* manager = dynamic_cast<Manager*>(system.users[i]))
		{
			ofs << "manager " << manager->getFirstName().c_str() << " "
				<< manager->getLastName().c_str() << " "
				<< manager->getPhoneNumber().c_str() << " "
				<< manager->getAge()<< " " << "1\n";
		}
		else if (Cashier* cashier = dynamic_cast<Cashier*>(system.users[i]))
		{
			ofs << "cashier " << cashier->getFirstName().c_str() << " "
				<< cashier->getLastName().c_str() << " "
				<< cashier->getPhoneNumber().c_str() << " "
				<< cashier->getAge() << " "
				<< cashier->checkIfApproved() << "\n";
		}
	}

	ofs.close();
}

void UserSystem::saveCurrentUser(const SupermarketSystem& system, const MyString& fileName)
{
	if (!system.currentUser)
	{
		return;	
	}


	if (fileName == "")
	{
		std::cout << "Save file for currentUser.txt corrupted or missing" << std::endl;
		return;
	}

	std::ofstream ofs(fileName.c_str());
	if (!ofs.is_open())
	{
		std::cout << "Cannot open currentUser.txt" << std::endl;
		return;
	}

	ofs << system.currentUser->getId() << "\n";

	ofs.close();
}

void UserSystem::loadCurrentUser(SupermarketSystem& system, const MyString& fileName)
{
	if (fileName == "")
	{
		std::cout << "Save file for currentUser.txt corrupted or missing" << std::endl;
		return;
	}

	std::ifstream ifs(fileName.c_str());
	if (!ifs.is_open())
	{
		std::cout << "Cannot open currentUser.txt" << std::endl;
		return;
	}

	unsigned id;
	ifs >> id;
	unsigned index = UserSystem::findUserIndex(system, id);
	system.currentUser = system.users[index];

	ifs.close();
}
