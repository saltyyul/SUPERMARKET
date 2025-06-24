#pragma once
#include "Giftcard.h"
#include "../MyString.h"

class MultipleCategoryGiftcard : public Giftcard
{
public:
	MultipleCategoryGiftcard(const MyString& code, double discountValue)
		:Giftcard(code,discountValue)
	{}

	Giftcard* clone() const override
	{
		return new MultipleCategoryGiftcard(*this);
	}

	MyString getType() const override
	{
		return "multiple";
	}
};