#pragma once
#include "MyString.h"
#include "User/Manager.h"

class Warning
{
private:
	MyString senderName;
	MyString description;
	unsigned points = 0;

	void copyFrom(const Warning& warning);
	void free();

public:
	Warning();
	Warning(const MyString& sender, const MyString& description, const unsigned points);

	Warning(const Warning& other);
	Warning& operator=(const Warning& other);

	~Warning();

	unsigned int getPoints() { return points; }

	void printInfo() const;

};