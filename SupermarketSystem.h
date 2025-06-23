#pragma once
#include <fstream>
#include <ctime>

#include "User/User.h"
#include "User/Cashier.h"
#include "User/Manager.h"
#include "Product/Category.h"
#include "Product/Product.h"
#include "Product/ProductByUnit.h"
#include "Product/ProductByWeight.h"
#include "./Giftcards/Giftcard.h"
#include "Giftcards/AllProductsGiftcard.h"
#include "Giftcards/MultipleCategoryGiftcard.h"
#include "Giftcards/SingleCategoryGiftcard.h"
#include "Warning.h"
#include "Feed.h"
#include "MyString.h"

class SupermarketSystem
{
private:

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
	
	void resizeUsers(unsigned newCap);
	void resizeCategories(unsigned newCap);
	void resizeProducts(unsigned newCap);
	void resizeGiftcards(unsigned newCap);

public:
	SupermarketSystem();

	~SupermarketSystem();

	void login(unsigned id, const MyString& password);
	void logout();

	struct Transaction;
	unsigned nextTransactionId = 1;

	void listUserData() const;
	void listWorkers() const;
	void listProducts() const;
	void listProductsByCategory(const unsigned categoryId) const;
	void listWarnedCashiers(unsigned points) const;

	void loadProducts(const MyString& fileName);
	void loadGiftcards(const MyString& fileName);

	void warnCashier(const MyString& name);
	void writeReceipt(unsigned cashierId, const Transaction* item, size_t count, double totalSum);
	void sell();
};