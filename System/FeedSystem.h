#pragma once
#include "../SupermarketSystem.h"

namespace FeedSystem
{
	void resizeFeed(SupermarketSystem& system, unsigned newCap);
	void listFeed(const SupermarketSystem& system);
	void addFeed(SupermarketSystem& system, const MyString& author, const MyString& description);

	void loadFeed(SupermarketSystem& system, const MyString& fileName);
	void saveFeed(const SupermarketSystem& system, const MyString& fileName);
}