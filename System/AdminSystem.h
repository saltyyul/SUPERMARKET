#pragma once
#include "../SupermarketSystem.h"
#include "FeedSystem.h"
#include "UserSystem.h"

namespace AdminSystem
{
	void listPending(const SupermarketSystem& system);
	void listWarnedCashiers(const SupermarketSystem& system, unsigned points);

	void approveCashier(SupermarketSystem& system, unsigned cashierId, const MyString& inputSpecialCode);
	void declineCashier(SupermarketSystem& system, unsigned cashierId, const MyString& inputSpecialCode);
	void warnCashier(SupermarketSystem& system, unsigned cashierId);
	void promoteCashier(SupermarketSystem& system, unsigned cashierId, const MyString& inputSpecialCode);
	void fireCashier(SupermarketSystem& system, unsigned cashierId, const MyString& inputSpecialCode);
}