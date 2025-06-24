#pragma once
#include "../MyString.h"

class Product
{
private:
	unsigned id = 0;
	MyString name;
	unsigned categoryId = 0;
	double price = 0.0;

	static unsigned nextId;
	static unsigned generateId();
	void copyFrom(const Product& other);

public:
	Product() = default;

	Product(const MyString& name, unsigned categoryId, const double price);

	Product(const Product& other);
	Product& operator=(const Product& other);

	virtual Product* clone() const = 0;

	virtual ~Product() = default;
	
	const unsigned getId() const;
	MyString getName() const;
	const unsigned getCategoryId() const;
	const double getPrice() const;

	virtual void print() const = 0;
	virtual bool sell(double quantity) = 0;
	virtual double getQuantity() const = 0;
};