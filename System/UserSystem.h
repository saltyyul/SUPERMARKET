#pragma once
#include "../SupermarketSystem.h"
#include "FeedSystem.h"

namespace UserSystem
{
	void resizeUsers(SupermarketSystem& system, unsigned newCap);
	int findUserIndex(SupermarketSystem& system, unsigned id);

	void login(SupermarketSystem& system, unsigned id, const MyString& password);
	void logout(SupermarketSystem& system);
	void leave(SupermarketSystem& system);
	void registerUser(SupermarketSystem& system, const char* input);

	void listUserData(const SupermarketSystem& system);
	void listWorkers(const SupermarketSystem& system);
}