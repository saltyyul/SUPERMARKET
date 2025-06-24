#include "AdminSystem.h"

void AdminSystem::listPending(const SupermarketSystem& system)
{
	if (!system.currentUser || system.currentUser->getRole() != "manager")
	{
		std::cout << "You don't have access to this command." << std::endl;
		return;
	}

	for (size_t i = 0; i < system.userCount; i++)
	{
		if (system.users[i]->getRole() == "cashier")
		{
			Cashier* cashier = dynamic_cast<Cashier*>(system.users[i]);
			if (!cashier->checkIfApproved())
			{
				cashier->printInfo();
			}
		}
		std::cout << "----------" << std::endl;
	}
}

void AdminSystem::listWarnedCashiers(const SupermarketSystem& system, unsigned points)
{
	if (!system.currentUser || system.currentUser->getRole() != "manager")
	{
		std::cout << "You don't have access to this command." << std::endl;
		return;
	}

	std::cout << "Warned cashiers with over " << points << " points:" << std::endl;
	for (size_t i = 0; i < system.userCount; i++)
	{
		if (system.users[i]->getRole() == "cashier")
		{
			Cashier* cashier = dynamic_cast<Cashier*>(system.users[i]);
			if (cashier->getWarningPoints() >= points && cashier->checkIfApproved())
			{
				cashier->printInfo();
			}
		}
	}
}

void AdminSystem::approveCashier(SupermarketSystem& system, unsigned cashierId, const MyString& inputSpecialCode)
{
	if (!system.currentUser || system.currentUser->getRole() != "manager")
	{
		std::cout << "You don't have access to this command." << std::endl;
		return;
	}

	unsigned userIndex = UserSystem::findUserIndex(system, cashierId);
	if (userIndex < 0)
	{
		std::cout << "Cashier not found or special code is wrong" << std::endl;
		return;
	}

	Manager* manager = dynamic_cast<Manager*>(system.currentUser);
	if (inputSpecialCode != manager->getSpecialCode())
	{
		std::cout << "Invalid special code" << std::endl;
		return;
	}

	if (system.users[userIndex]->getRole() == "cashier")
	{
		Cashier* cashier = dynamic_cast<Cashier*>(system.users[userIndex]);
		cashier->setApproval();
		std::cout << "Approved cashier" << cashier->getId() << std::endl;
		FeedSystem::addFeed(system, system.currentUser->getFullName(), "Approved cashier" + cashier->getId());

		return;
	}

	std::cout << "User does not have a cashier role" << std::endl;
}

void AdminSystem::declineCashier(SupermarketSystem& system, unsigned cashierId, const MyString& inputSpecialCode)
{
	if (!system.currentUser || system.currentUser->getRole() != "manager")
	{
		std::cout << "You don't have access to this command." << std::endl;
		return;
	}

	unsigned userIndex = UserSystem::findUserIndex(system, cashierId);
	if (userIndex < 0)
	{
		std::cout << "Cashier not found" << std::endl;
		return;
	}

	Manager* manager = dynamic_cast<Manager*>(system.currentUser);
	if (inputSpecialCode != manager->getSpecialCode())
	{
		std::cout << "Invalid special code" << std::endl;
		return;
	}

	if (system.users[userIndex]->getRole() == "cashier")
	{
		Cashier* cashier = dynamic_cast<Cashier*>(system.users[userIndex]);
		if (cashier->checkIfApproved())
		{
			std::cout << "Cashier already approved. "
				<< "Perhaps you want to try fire_cashier <cashier_id> <special_code>. " << std::endl;
		}

		delete system.users[userIndex];
		for (size_t i = userIndex; i < system.userCount - 1; i++)
		{
			system.users[i] = system.users[i + 1];
		}
		system.userCount--;
		std::cout << "Cashier declined" << std::endl;
		FeedSystem::addFeed(system, system.currentUser->getFullName(), "Declined cashier.");
		return;
	}

	std::cout << "User does not have a cashier role" << std::endl;
}

void AdminSystem::warnCashier(SupermarketSystem& system, unsigned cashierId)
{
	if (!system.currentUser || system.currentUser->getRole() != "manager")
	{
		std::cout << "You don't have access to this command." << std::endl;
		return;
	}

	unsigned userIndex = UserSystem::findUserIndex(system, cashierId);
	if (userIndex < 0)
	{
		std::cout << "Cashier not found" << std::endl;
		return;
	}

	if (system.users[userIndex]->getRole() == "cashier")
	{
		std::cout << "Warning description: " << std::endl;
		char input[Constants::MAX_BUFFER_SIZE];
		std::cin.ignore();
		std::cin.getline(input, sizeof(input));

		std::cout << "Warning severity points:" << std::endl;
		unsigned points;
		std::cin >> points;

		Warning w(system.currentUser->getFullName(), MyString(input), points);
		Cashier* cashier = dynamic_cast<Cashier*>(system.users[userIndex]);

		if (!cashier->checkIfApproved())
		{
			std::cout << "Cashier waits for approval, you can't add a warning" << std::endl;
			return;
		}

		cashier->addWarning(w);

		std::cout << "Warning added" << std::endl;
		FeedSystem::addFeed(system, system.currentUser->getFullName(), "Warned cashier" + cashier->getFullName());
		return;
	}

	std::cout << "Cannot find cashier " << std::endl;
}

void AdminSystem::promoteCashier(SupermarketSystem& system, unsigned cashierId, const MyString& inputSpecialCode)
{
	if (!system.currentUser || system.currentUser->getRole() != "manager")
	{
		std::cout << "You don't have access to this command." << std::endl;
		return;
	}
	unsigned userIndex = UserSystem::findUserIndex(system, cashierId);
	if (userIndex < 0)
	{
		std::cout << "Cashier not found" << std::endl;
		return;
	}

	Cashier* cashier = dynamic_cast<Cashier*>(system.users[userIndex]);
	if (!cashier)
	{
		std::cout << "User is not a cashier" << std::endl;
		return;
	}

	Manager* newManager = new Manager(MyString(cashier->getFirstName()), MyString(cashier->getLastName()),
		MyString(cashier->getPhoneNumber()), cashier->getAge(), MyString(cashier->getPass()));
	delete system.users[userIndex];
	system.users[userIndex] = newManager;
	std::cout << "Cashier " << newManager->getFullName() << "promoted." << std::endl;
	FeedSystem:: addFeed(system, system.currentUser->getFullName(), "Promoted " + newManager->getFullName());
}

void AdminSystem::fireCashier(SupermarketSystem& system, unsigned cashierId, const MyString& inputSpecialCode)
{
	if (!system.currentUser || system.currentUser->getRole() != "manager")
	{
		std::cout << "You don't have access to this command." << std::endl;
		return;
	}

	unsigned userIndex = UserSystem::findUserIndex(system, cashierId);
	if (userIndex < 0)
	{
		std::cout << "Cashier not found" << std::endl;
		return;
	}

	delete system.users[userIndex];
	for (size_t i = userIndex; i < system.userCount - 1; i++)
	{
		system.users[i] = system.users[i + 1];
	}
	system.userCount--;
	std::cout << "Cashier fired" << std::endl;
	FeedSystem::addFeed(system, system.currentUser->getFullName(), "Fired cashier");
}