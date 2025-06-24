#pragma once
#include "../MyString.h"
#include "Giftcard.h"

class AllProductsGiftcard : public Giftcard
{
public:
	AllProductsGiftcard(const MyString& code, double discountValue)
		:Giftcard(code, discountValue)
	{}

	Giftcard* clone() const override
	{
		return new AllProductsGiftcard(*this);
	}

	MyString getType() const override
	{
		return "all";
	}
};