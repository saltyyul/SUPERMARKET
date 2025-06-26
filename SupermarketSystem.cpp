#include "SupermarketSystem.h"
#include <iostream>

#pragma warning (disable: 4996)

MyString SupermarketSystem::getCurrentDate() const
{
	time_t curr = time(0);
	tm* localTime = localtime(&curr);
	char dateBuff[Constants::MAX_BUFFER_SIZE];
	strftime(dateBuff, sizeof(dateBuff), "%Y-%m-%d %H:%M:%S", localTime);

	return MyString(dateBuff);
}

SupermarketSystem::SupermarketSystem()
{
	userCapacity = categoryCapacity = productCapacity = giftCapacity = tranCapacity = feedCapacity = 8;

	users = new User * [userCapacity];
	categories = new Category * [categoryCapacity];
	products = new Product * [productCapacity];
	giftcards = new Giftcard * [giftCapacity];
	transactions = new Transaction * [tranCapacity];
	feed = new Feed * [feedCapacity];
}

SupermarketSystem:: ~SupermarketSystem()
{
	for (size_t i = 0; i < feedCount; i++)
	{
		delete feed[i];
	}
	delete[] feed;

	for (size_t i = 0; i < tranCount; i++)
	{
		delete transactions[i];
	}
	delete[] transactions;

	for (size_t i = 0; i < userCount; i++)
	{
		delete users[i];
	}
	delete[] users;

	for (size_t i = 0; i < prodcutCount; i++)
	{
		delete products[i];
	}
	delete[] products;

	for (size_t i = 0; i < giftCount; i++)
	{
		delete giftcards[i];
	}
	delete[] giftcards;

	for (size_t i = 0; i < categoryCount; i++)
	{
		delete categories[i];
	}
	delete[] categories;

	userCount = categoryCount = prodcutCount = categoryCount = tranCount = feedCount = 0;
}




