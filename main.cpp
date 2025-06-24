#include <iostream>
#include "SupermarketSystem.h"
#include "System/AdminSystem.h"
#include "System/FeedSystem.h"
#include "System/ProductSystem.h"
#include "System/TransactionSystem.h"
#include "System/UserSystem.h"

#pragma warning (disable: 4996)


size_t splitIntoTokens(char* input, char* tokens[])
{
	size_t count = 0;
	char* token = strtok(input, " ");

	while (token && count < Constants::MAX_TOKEN_COUNT)
	{
		tokens[count++] = token;
		token = strtok(nullptr, " ");

	}

	return count;
}

int main()
{
	std::cout << "Welcome to FMI Supermarket Management System 2024 - 2025!" << std::endl;
	SupermarketSystem sys;
	UserSystem::loadUsersFromFile(sys, "users.txt");

	if (sys.userCount == 0)
	{
		UserSystem::registerUser(sys, MyString("manager"), MyString("Admin"), MyString("Admin"),
			MyString("00000"), 26, MyString("admin"));
	}

	while (true)
	{
		std::cout << "Please choose an action: " << std::endl;
		std::cout << ">";
		char buff[Constants::MAX_BUFFER_SIZE];
		std::cin.clear();
		std::cin.getline(buff, Constants::MAX_BUFFER_SIZE);

		char* tokens[Constants::MAX_TOKEN_COUNT]{ nullptr };
		size_t tokenCount = splitIntoTokens(buff, tokens);

		if (tokenCount == 0 || !tokens[0])
		{
			continue;
		}

		const char* comm = tokens[0];

		if (strcmp(comm, "exit") == 0)
		{
			std::cout << "Exited the system!" << std::endl;
			break;
		}
		else if (strcmp(comm, "login") == 0 && tokenCount == 3)
		{
			unsigned id = atoi(tokens[1]);
			UserSystem::login(sys, id, MyString(tokens[2]));
		}
		else if (strcmp(comm, "logout") == 0 && tokenCount == 1)
		{
			UserSystem::logout(sys);
		}
		else if (strcmp(comm, "register") == 0 && tokenCount == 7)
		{
			unsigned age = atoi(tokens[5]);
			UserSystem::registerUser(sys, MyString(tokens[1]), MyString(tokens[2]), MyString(tokens[3]),
				MyString(tokens[4]), age, MyString(tokens[6]));
		}
		else if (strcmp(comm, "list_user_data") == 0 && tokenCount == 1)
		{
			UserSystem::listUserData(sys);
		}
		else if (strcmp(comm, "list_workers") == 0 && tokenCount == 1)
		{
			UserSystem::listWorkers(sys);
		}
		else if (strcmp(comm, "list_products") == 0 && tokenCount == 1)
		{
			ProductSystem::listProducts(sys);
		}
		else if (strcmp(comm, "list_products") == 0 && tokenCount == 2)
		{
			unsigned categoryId = atoi(tokens[1]);
			ProductSystem::listProductsByCategory(sys, categoryId);
		}
		else if (strcmp(comm, "list_feed") == 0 && tokenCount == 1)
		{
			FeedSystem::listFeed(sys);
		}
		else if (strcmp(comm, "list_transactions") == 0 && tokenCount == 1)
		{
			TransactionSystem::listTransactions(sys);
		}
		else if (strcmp(comm, "leave") == 0 && tokenCount == 1)
		{
			UserSystem::leave(sys);
		}
		else if (strcmp(comm, "list_pending") == 0 && tokenCount == 1)
		{
			AdminSystem::listPending(sys);
		}
		else if (strcmp(comm, "approve") == 0 && tokenCount == 3)
		{
			unsigned cashierId = atoi(tokens[1]);
			AdminSystem::approveCashier(sys, cashierId, MyString(tokens[2]));
		}
		else if (strcmp(comm, "decline") == 0 && tokenCount == 3)
		{
			unsigned cashierId = atoi(tokens[1]);
			AdminSystem::declineCashier(sys, cashierId, MyString(tokens[2]));
		}
		else if (strcmp(comm, "list_warned") == 0 && tokenCount == 2)
		{
			unsigned points = atoi(tokens[1]);
			AdminSystem::listWarnedCashiers(sys, points);
		}
		else if (strcmp(comm, "promote") == 0 && tokenCount == 3)
		{
			unsigned cashierId = atoi(tokens[1]);
			AdminSystem::promoteCashier(sys, cashierId, MyString(tokens[2]));
		}
		else if (strcmp(comm, "fire") == 0 && tokenCount == 3)
		{
			unsigned cashierId = atoi(tokens[1]);
			AdminSystem::fireCashier(sys, cashierId, MyString(tokens[2]));
		}
		else if (strcmp(comm, "add_category") == 0 && tokenCount == 3)
		{
			ProductSystem::addCategory(sys, MyString(tokens[1]), MyString(tokens[2]));
		}
		else if (strcmp(comm, "delete_category") == 0 && tokenCount == 2)
		{
			unsigned categoryId = atoi(tokens[1]);
			ProductSystem::deleteCategory(sys, categoryId );
		}
		else if (strcmp(comm, "add_product") == 0 && tokenCount == 2)
		{
			ProductSystem::addProduct(sys, MyString(tokens[1]));
		}
		else if (strcmp(comm, "delete_prodcut") == 0 && tokenCount == 2)
		{
			unsigned productId = atoi(tokens[1]);
			ProductSystem::deleteProduct(sys, productId);
		}
		else if (strcmp(comm, "load_products") == 0 && tokenCount == 2)
		{
			ProductSystem::loadProducts(sys, MyString(tokens[1]));
		}
		else if (strcmp(comm, "load_giftcards") == 0 && tokenCount == 2)
		{
			ProductSystem::loadGiftcards(sys, MyString(tokens[1]));
		}
		else
		{
			std::cout << "Invalid command" << std::endl;
		}
	}

	//saveUsers(sys, "users.txt");
}