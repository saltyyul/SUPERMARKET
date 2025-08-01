#pragma once
#include "../MyString.h"

class User 
{
protected:
	unsigned id = 0;
	MyString firstName;
	MyString lastName;
	MyString phoneNumber;
	unsigned age = 0;
	MyString pass;

	static unsigned nextId;
	static unsigned generateId();

	void copyFrom(const User& other);
	void free();

public:
	User(const MyString& fn, const MyString& ln, const MyString& phoneNum, const unsigned age, const MyString& pass);

	User(const User& other);
	User& operator=(const User& other);

	virtual ~User();

	const unsigned getId() const;
	MyString getFirstName() const;
	MyString getLastName() const;
	MyString getFullName() const;
    MyString getPhoneNumber() const;
	const unsigned getAge() const;
	MyString getPass() const;
	
	void setName(const MyString& fn, const MyString& ln);
	void setAge(const unsigned age);
	void setPhoneNumber(const MyString& phoneNum);
	
	virtual void printInfo() const;
	virtual MyString getRole() const;
};