#pragma once
#include <fstream>
#include <ctime>

#include "./User/User.h"
#include "./User/Cashier.h"
#include "./User/Manager.h"
#include "./Product/Category.h"
#include "./Product/Product.h"
#include "./Product/ProductByUnit.h"
#include "./Product/ProductByWeight.h"
#include "./Giftcards/Giftcard.h"
#include "./Giftcards/AllProductsGiftcard.h"
#include "./Giftcards/MultipleCategoryGiftcard.h"
#include "./Giftcards/SingleCategoryGiftcard.h"
#include "./User/Warning.h"
#include "./Feed/Feed.h"
#include "./Transaction/Transaction.h"
#include "MyString.h"

class SupermarketSystem
{
public:
	SupermarketSystem();
	~SupermarketSystem();

	SupermarketSystem(const SupermarketSystem& other) = delete;
	SupermarketSystem& operator=(const SupermarketSystem& other) = delete;

	User* currentUser = nullptr;

	User** users = nullptr;
	unsigned userCount = 0;
	unsigned userCapacity = 0;

	Category** categories = nullptr;
	unsigned categoryCount = 0;
	unsigned categoryCapacity = 0;

	Product** products = nullptr;
	unsigned prodcutCount = 0;
	unsigned productCapacity = 0;

	Giftcard** giftcards = nullptr;
	unsigned giftCount = 0;
	unsigned giftCapacity = 0;

	Transaction** transactions = nullptr;
	unsigned tranCount = 0;
	unsigned tranCapacity = 0;

	Feed** feed = nullptr;
	unsigned feedCount = 0;
	unsigned feedCapacity = 0;

	const MyString& getCurrentDate() const;
};