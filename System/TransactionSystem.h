#pragma once
#include "../SupermarketSystem.h"
#include "FeedSystem.h"

#pragma warning (disable: 4996)
namespace TransactionSystem
{
	void resizeTransactions(SupermarketSystem& system, unsigned newCap);

	void listTransactions(const SupermarketSystem& system);

	void sell(SupermarketSystem& system);
	void addTransaction(SupermarketSystem& system, Transaction* transaction);

	void loadTransaction(SupermarketSystem& system, const MyString& fileName);
	void saveTransaction(const SupermarketSystem& system, const MyString& fileName);
}