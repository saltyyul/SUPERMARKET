#pragma once
#include "Product.h"
#include <iostream>

class ProductByWeight : public Product
{
private:
	double weight;

public:
	ProductByWeight(const MyString& name, unsigned categoryId, const double price, double weight)
		:Product(name, categoryId, price)
	{
		this->weight = weight;
	}

	Product* clone() const override
	{
		return new ProductByWeight(*this);
	}

	void print() const override
	{
		std::cout << getName() << " : " << getPrice() << "/kg : " << weight << std::endl;
	}

	bool sell(double quantity)
	{
		if (quantity > weight)
		{
			std::cout << "Out of stock" << std::endl;
			return false;
		}
		weight -= quantity;
		return true;
	}
	double getQuantity() const
	{
		return weight;
	}
};