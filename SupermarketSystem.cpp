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
	userCapacity = categoryCapacity = productCapacity = 8;

	users = new User * [userCapacity];
	categories = new Category * [categoryCapacity];
	products = new Product * [productCapacity];
	giftcards = new Giftcard * [giftCapacity];
	transactions = new Transaction * [tranCapacity];
	feed = new Feed * [feedCapacity];
}

SupermarketSystem:: ~SupermarketSystem()
{
	userCount = categoryCount = prodcutCount = 0;
}




