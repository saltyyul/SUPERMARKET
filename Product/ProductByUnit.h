#pragma once
#include "Product.h"
#include <iostream>

class ProductByUnit : public Product 
{
private:
	unsigned unitCount = 0;

public:
	ProductByUnit(const MyString& name, unsigned categoryId, const double price, unsigned unitCount)
		:Product(name, categoryId, price)
	{
		this->unitCount = unitCount;
	}
	 
	Product* clone() const override
	{
		return new ProductByUnit(*this);
	}

	void print() const override
	{
		std::cout << getName() << " : " << getPrice() << " : " << unitCount<<std::endl;
	}

	bool sell(double quantity)
	{
		if ((unsigned)quantity > unitCount)
		{
			std::cout << "Out of stock" << std::endl;
			return false;
		}
		unitCount -= quantity;
		return true;
	}

	double getQuantity() const
	{
		return (double)unitCount;
	}
};