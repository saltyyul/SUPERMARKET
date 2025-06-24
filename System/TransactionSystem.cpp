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
	if (!system.currentUser || system.currentUser->getRole() != "Cashier")
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
		std::cout << "Enter product ID to sell. Enter END to end the transaction: " << std::endl;
		std::cin >> input;

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
	if (strcmp(input, "y") == 0)
	{
		std::cout << "Enter voucher:" << std::endl;
		std::cin >> input;

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

