#pragma once
#include "../SupermarketSystem.h"
#include "FeedSystem.h"

namespace TransactionSystem
{
	void resizeTransactions(SupermarketSystem& system, unsigned newCap);

	void listTransactions(const SupermarketSystem& system);

	void sell(SupermarketSystem& system);
	void addTransaction(SupermarketSystem& system, Transaction* transaction);
}