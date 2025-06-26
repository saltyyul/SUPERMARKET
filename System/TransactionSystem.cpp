#include "TransactionSystem.h"

void TransactionSystem::resizeTransactions(SupermarketSystem& system, unsigned newCap)
{
	Transaction** newTransactions = new Transaction * [newCap] {};

	for (size_t i = 0; i < system.tranCount; i++)
	{
		newTransactions[i] = system.transactions[i];
	}

	delete[]  system.transactions;
	system.transactions = newTransactions;

	system.tranCapacity = newCap;
}


void TransactionSystem::listTransactions(const SupermarketSystem& system)
{
	if (system.tranCount < 0)
	{
		std::cout << "No transactions" << std::endl;
		return;
	}

	for (size_t i = 0; i < system.tranCount; i++)
	{
		system.transactions[i]->printInfo();
	}
}


void TransactionSystem::sell(SupermarketSystem& system)
{
	if (!system.currentUser || system.currentUser->getRole() != "cashier")
	{
		std::cout << "You don't have access to this command." << std::endl;
		return;
	}

	Cashier* cashier = dynamic_cast<Cashier*>(system.currentUser);
	if (!cashier || !cashier->checkIfApproved())
	{
		std::cout << "Invalid cashier or not approved" << std::endl;
		return;
	}

	MyString date = system.getCurrentDate();
	Transaction* transaction = new Transaction(system.currentUser->getId(), date);

	char input[Constants::MAX_BUFFER_SIZE];
	while (true)
	{
		std::cout << "Enter product ID to sell. Enter 'end' to end the transaction: " << std::endl;
		std::cin >> input;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (strcmp(input, "end") == 0) break;
		unsigned id = atoi(input);

		Product* product = nullptr;
		for (size_t i = 0; i < system.prodcutCount; i++)
		{
			if (system.products[i]->getId() == id)
			{
				product = system.products[i];
				break;
			}
		}

		if (!product)
		{
			std::cout << "Invalid product" << std::endl;
			return;
		}

		std::cout << "Enter quantity: " << std::endl;
		double quantity;
		std::cin >> quantity;
		if (!product->sell(quantity))
		{
			continue;
		}

		transaction->addProduct(product, quantity);
	}

	std::cout << "Add voucher: (Y/N) ?" << std::endl;
	std::cin >> input;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	if (strcmp(input, "y") == 0)
	{
		std::cout << "Enter voucher:" << std::endl;
		std::cin >> input;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		for (size_t i = 0; i < system.giftCount; i++)
		{
			if (strcmp(system.giftcards[i]->getCode().c_str(), input) == 0)
			{
				transaction->applyDiscount(system.giftcards[i]->getDiscountValue());
				std::cout << "Discount applied!" << std::endl;
				break;
			}
		}
	}
	std::cout << "Transaction complete!" << std::endl;

	transaction->printReceipt();

	cashier->addTransaction();
	if (cashier->getTransactionCount() % 3 == 0)
	{
		cashier->removeOldestWarning();
	}
	FeedSystem::addFeed(system, system.currentUser->getFullName(), "Assisted a purchase");
}

void TransactionSystem::addTransaction(SupermarketSystem& system, Transaction* transaction)
{
	if (system.tranCount >= system.tranCapacity)
	{
		resizeTransactions(system, system.tranCount * 2);
	}
	system.transactions[system.tranCount++] = transaction;
}

void TransactionSystem::loadTransaction(SupermarketSystem& system, const MyString& fileName)
{
	if (fileName == "")
	{
		std::cout << "Save file for transactions.txt corrupted or missing" << std::endl;
		return;
	}
	std::ifstream ifs(fileName.c_str());
	if (!ifs.is_open()) 
	{
		//std::cout << "Cannot open transactions.txt"<<std::endl;
		return;
	}

	char buff[Constants::MAX_BUFFER_SIZE];
	Transaction* current = nullptr;
	unsigned cashierId = 0;
	MyString date = "";

	while (ifs.getline(buff, sizeof(buff))) 
	{
		if (strcmp(buff, "start") == 0) 
		{
			cashierId = 0;
			date = "";
			current = nullptr;
		}
		else if (strncmp(buff, "cashierId,", 10) == 0)
		{
			cashierId = atoi(buff + 10);
		}
		else if (strncmp(buff, "date,", 5) == 0)
		{
			date = MyString(buff + 5);
			current = new Transaction(cashierId, date);
		}
		else if (strncmp(buff, "product,", 8) == 0)
		{
			char* token = strtok(buff, ",");
			char* idStr = strtok(nullptr, ","); 
			char* quantityStr = strtok(nullptr, ",");

			if (idStr && quantityStr && current)
			{
				unsigned productId = atoi(idStr);
				double quantity = atof(quantityStr);

				for (size_t i = 0; i < system.prodcutCount; i++)
				{
					if (system.products[i]->getId() == productId) 
					{
						current->addProduct(system.products[i], quantity);
						break;
					}
				}
			}
		}
		else if (strcmp(buff, "end") == 0) 
		{
			if (current) 
			{
				if (system.tranCount >= system.tranCapacity)
				{
					resizeTransactions(system, system.tranCount * 2);
				}
				system.transactions[system.tranCount++] = current;
				current = nullptr;
			}
		}
	}

	ifs.close();
}

void TransactionSystem::saveTransaction(const SupermarketSystem& system, const MyString& fileName)
{
	if (fileName == "")
	{
		std::cout << "Save file for transactions.txt corrupted or missing" << std::endl;
		return;
	}
	std::ofstream ofs(fileName.c_str());
	if (!ofs.is_open()) {
		std::cout << "Cannot open transactions.txt"<<std::endl;
		return;
	}

	for (size_t i = 0; i < system.tranCount; i++) 
	{
		Transaction* transaction = system.transactions[i];

		ofs << "start\n";
		ofs << "cashierId," << transaction->getCashierId() << "\n";
		ofs << "date," << transaction->getDate().c_str() << "\n";

		for (size_t j = 0; j < transaction->getProductCount(); j++) {
			ofs << "product," << transaction->getProduct(j)->getId()
				<< "," << transaction->getQuantity(j) << "\n";
		}

		ofs << "total," << transaction->getTotal() << "\n";
		ofs << "end\n";
	}

	ofs.close();
}

