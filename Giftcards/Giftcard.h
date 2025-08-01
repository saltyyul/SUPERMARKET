#pragma once
#include "../MyString.h"

class Giftcard
{
protected:
	MyString code;
	double discountValue;

public: 
	Giftcard(const MyString& code, double discountValue)
		:code(code), discountValue(discountValue)
	{}

	virtual ~Giftcard() = default;

	virtual Giftcard* clone() const = 0;
	virtual MyString getType() const = 0;

	MyString getCode() const { return code; }
	double getDiscountValue() const { return discountValue; }
};