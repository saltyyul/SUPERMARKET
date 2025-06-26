#pragma once
#include "../SupermarketSystem.h"
#include "FeedSystem.h"

namespace ProductSystem
{
	void resizeProducts(SupermarketSystem& system, unsigned newCap);
	void resizeCategories(SupermarketSystem& system, unsigned newCap);
	void resizeGiftcards(SupermarketSystem& system, unsigned newCap);

	void listProducts(const SupermarketSystem& system);
	void listProductsByCategory(const SupermarketSystem& system, const unsigned categoryId);

	void loadProducts(SupermarketSystem& system, const MyString& fileName);
	void loadGiftcards(SupermarketSystem& system, const MyString& fileName);

	void saveProducts(const SupermarketSystem& system, const MyString& fileName);
	void saveGiftcards(const SupermarketSystem& system, const MyString& fileName);

	void addCategory(SupermarketSystem& system, const MyString& name, const MyString& description);
	void deleteCategory(SupermarketSystem& system, unsigned categoryId);
	void addProduct(SupermarketSystem& system, const MyString& type);
	void deleteProduct(SupermarketSystem& system, unsigned productId);
}