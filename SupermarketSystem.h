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
#include "Transaction.h"
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

	Transaction** transactions = nullptr;
	unsigned tranCount = 0;
	unsigned tranCapacity = 0;

	Feed** feed = nullptr;
	unsigned feedCount = 0;
	unsigned feedCapacity = 0;
	
	void resizeUsers(unsigned newCap);
	void resizeCategories(unsigned newCap);
	void resizeProducts(unsigned newCap);
	void resizeGiftcards(unsigned newCap);
	void resizeTransactions(unsigned newCap);
	void resizeFeed(unsigned newCap);

public:
	SupermarketSystem();

	~SupermarketSystem();

	void login(unsigned id, const MyString& password);
	void logout();
	void leave();
	void registerUser(const char* input);

	const MyString& getCurrentDate() const;
	int findUserIndex(unsigned id) const;

	void listUserData() const;
	void listWorkers() const;
	void listProducts() const;
	void listProductsByCategory(const unsigned categoryId) const;
	void listFeed() const;
	void listTransactions() const;
	void listPending() const;
	void listWarnedCashiers(unsigned points) const;

	void loadProducts(const MyString& fileName);
	void loadGiftcards(const MyString& fileName);

	void approveCashier(unsigned cashierId, const MyString& inputSpecialCode);
	void declineCashier(unsigned cashierId, const MyString& inputSpecialCode);
	void warnCashier(unsigned cashierId);
	void promoteCashier(unsigned cashierId, const MyString& inputSpecialCode);
	void fireCashier(unsigned cashierId, const MyString& inputSpecialCode);

	void sell();
	void addTransaction(Transaction* transaction);
	void addFeed(const MyString& author, const MyString& description);
	void addCategory(const MyString& name, const MyString& description);
	void deleteCategory(unsigned categoryId);
	void addProduct(const MyString& type);
	void deleteProduct(unsigned productId);
};