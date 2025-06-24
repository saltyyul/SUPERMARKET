#pragma once
#include "../MyString.h"
#include "../Product/Product.h"
#include "../Constants.h"
#include <iostream>
#include <fstream>

class Transaction
{
private:
	unsigned transactionId = 0;
	double total = 0.0;
	MyString date;
	unsigned cashierId = 0;

	Product** products = nullptr;
	double* quantities = nullptr;
	unsigned productCount = 0;
	unsigned productCapacity;

	static unsigned nextId;
	static unsigned generateId();

	void copyFrom(const Transaction& other);
	void resize(unsigned newCapacity);
	void free();

public:
	Transaction(unsigned cashierId, const MyString& date);

	Transaction(const Transaction& other);
	Transaction& operator= (const Transaction& other);
	
	~Transaction();

	void addProduct(Product* product, double quantity);
	void applyDiscount(double value);

	void printReceipt() const;
	void printInfo() const;
};