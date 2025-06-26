#include "Manager.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

constexpr unsigned SPECIAL_CODE_MAX = 8;

MyString Manager::generateSpecialCode() const
{
	char temp[SPECIAL_CODE_MAX];

	for (size_t i = 0; i < SPECIAL_CODE_MAX - 1; i++)
	{
		if (i == 1 || i == 2) 
		{
			temp[i] = 'A' + rand() % 26;
		}
		else if (i == 6)
		{
			temp[i] = 'a' + rand() % 26;
		}
		else temp[i] = '0' + rand() % 10;
	}
	temp[7] = '\0';

	return temp;
}

void Manager::saveSpecialCode() const
{
	MyString fileName = MyString(MyString::to_string(id)) + "_special_code.txt";

	std::ofstream ofs(fileName.c_str());
	if (!ofs.is_open())
	{
		std::cout << "Cannot open file" << std::endl;
		return;
	}
	ofs << specialCode;
	ofs.close();
}

Manager::Manager(const MyString& fn, const MyString& ln,
	const MyString& phoneNum, const unsigned age, const MyString& pass)
	:User(fn, ln, phoneNum, age, pass)
{
	this->specialCode = generateSpecialCode();
	saveSpecialCode();
}

MyString Manager::getSpecialCode() const
{
	return specialCode;
}

MyString Manager::getRole() const
{
	return "manager";
}

void Manager::printInfo() const
{
	User::printInfo();
	std::cout << "Role: " << getRole() << std::endl;
}