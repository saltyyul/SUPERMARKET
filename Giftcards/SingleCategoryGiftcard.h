#pragma once
#include "../MyString.h"
#include "Giftcard.h"

class SingleCategoryGiftcard: public Giftcard
{
public:
	SingleCategoryGiftcard(const MyString& code, double value)
		:Giftcard(code, value)
	{}

	Giftcard* clone() const override
	{
		return new SingleCategoryGiftcard(*this);
	}

	MyString getType() const override
	{
		return "single";
	}
};