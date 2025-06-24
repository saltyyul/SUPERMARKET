#include "User.h"
#include <iostream>

constexpr int MIN_USER_AGE = 18;
constexpr int MAX_PHONENUM_LEN = 10;

unsigned User::nextId = 100;

unsigned User::generateId()
{
	return nextId++;
}

void User::copyFrom(const User& other)
{
	id = other.id;
	firstName = other.firstName;
	lastName = other.lastName;
	phoneNumber = other.phoneNumber;
	age = other.age;
	pass = other.pass;
}

void User::free()
{ 
}

User::User(const MyString& fn, const MyString& ln,
	const MyString& phoneNum, const unsigned age, const MyString& pass)
{
	setName(fn, ln);
	setAge(age);
	setPhoneNumber(phoneNum);
	this->pass = pass;
	this->id = generateId();
}

User::User(const User& other)
{
	copyFrom(other);
}

User& User::operator=(const User& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

User::~User()
{
	free();
}

const unsigned User::getId() const { return id; }

MyString User::getFirstName() const { return firstName; }

MyString User::getLastName() const { return lastName; }

MyString User::getFullName() const { return firstName + " " + lastName; }

MyString User::getPhoneNumber() const { return phoneNumber; }

const unsigned User::getAge() const { return age; }

MyString User::getPass() const { return pass; }

void User::setName(const MyString& fn, const MyString& ln)
{
	if (fn == "" || ln == "" || this->firstName==fn||this->lastName == ln)
	{
		throw std::invalid_argument("Invalid first or last name");
		return;
	}

	firstName = fn;
	lastName = ln;
}

void User::setAge(const unsigned age)
{
	if (age < MIN_USER_AGE)
	{
		throw std::invalid_argument("Invalid age");
		return;
	}

	this->age = age;
}

bool checkPhoneNumber(const MyString& phoneNum)
{
	if (phoneNum.getLen() > MAX_PHONENUM_LEN) return false;

	for (size_t i = 0; i < phoneNum.getLen(); i++)
	{
		if (phoneNum[i] < '0' || phoneNum[i]>'9')
		{
			return false;
		}
	}

	return true;
}

void User::setPhoneNumber(const MyString& phoneNum)
{
	if (!checkPhoneNumber(phoneNum))
	{
		throw std::invalid_argument("Invalid phone number");
		return;
	}

	this->phoneNumber = phoneNum;
}

void User::printInfo() const
{
	std::cout << "Id: " << id <<
		"\n Name: " << firstName << " " << lastName <<
		"\n Age: " << age <<
		"\n Phone: " << phoneNumber << "\n";
}

MyString User::getRole() const
{
	return "Unknown";
}