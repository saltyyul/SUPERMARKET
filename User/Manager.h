#pragma once
#include "User.h"

class Manager : public User
{
private:
	MyString specialCode;

	MyString generateSpecialCode() const;
	void saveSpecialCode() const;

public:
	Manager(const MyString& fn, const MyString& ln, const MyString& phoneNum,
		const unsigned age, const MyString& pass);

	const MyString& getSpecialCode() const;
	const MyString& getRole() const;

	void printInfo() const;
};