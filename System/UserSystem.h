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
	void registerUser(SupermarketSystem& system, const MyString& role, const MyString& fn,
		const MyString& ln, const MyString& phone, unsigned age, const MyString& pass);

	void listUserData(const SupermarketSystem& system);
	void listWorkers(const SupermarketSystem& system);

	void loadUsersFromFile(SupermarketSystem& system, const MyString& fileName);
	void saveUsers(const SupermarketSystem& system, const MyString& fileName);
	void saveCurrentUser(const SupermarketSystem& system, const MyString& fileName);
	void loadCurrentUser(SupermarketSystem& system, const MyString& fileName);
}