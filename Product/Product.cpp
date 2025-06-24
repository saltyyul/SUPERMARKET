#include "Product.h"

unsigned Product::nextId = 1;

unsigned  Product::generateId()
{
	return nextId++;
}

void Product::copyFrom(const Product& other)
{
	id = other.id;
	name = other.name;
	categoryId = other.categoryId;
	price = other.price;
}

Product::Product(const MyString& name, unsigned categoryId, const double price)
{
	this->id = generateId();
	this->name = name;
	this->categoryId = categoryId;
	this->price = price;
}

Product::Product(const Product& other)
{
	copyFrom(other);
}

Product& Product::operator=(const Product& other)
{
	if (this != &other)
	{
		copyFrom(other);
	}

	return *this;
}

const unsigned Product::getId() const
{
	return id;
}
MyString Product::getName() const
{
	return name;
}
const unsigned Product::getCategoryId() const
{
	return categoryId;
}

const double Product::getPrice() const
{
	return price;
}