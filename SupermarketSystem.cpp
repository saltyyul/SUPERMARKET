#include "SupermarketSystem.h"
#include <iostream>

#pragma warning (disable: 4996)

const unsigned MAX_BUFFER_SIZE = 256;

const MyString& SupermarketSystem::getCurrentDate() const
{
	time_t curr = time(0);
	tm* localTime = localtime(&curr);
	char dateBuff[MAX_BUFFER_SIZE];
	strftime(dateBuff, sizeof(dateBuff), "%Y-%m-%d %H:%M:%S", localTime);

	return MyString(dateBuff);
}

SupermarketSystem::SupermarketSystem()
{
	userCapacity = categoryCapacity = productCapacity = 8;

	users = new User * [userCapacity];
	categories = new Category * [categoryCapacity];
	products = new Product * [productCapacity];
}

SupermarketSystem:: ~SupermarketSystem()
{
	userCount = categoryCount = prodcutCount = 0;
}




