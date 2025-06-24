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
	for (size_t i = 0; i < system.userCount; i++)
	{
		if (id == system.users[i]->getId() && password == system.users[i]->getPass())
		{
			system.currentUser = system.users[i];
			std::cout << "User " << system.currentUser->getFullName()
				<< " with ID: " << system.currentUser->getId()
				<< " has been logged into this system!" << std::endl;
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