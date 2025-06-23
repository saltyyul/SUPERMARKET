#pragma once
#include "../MyString.h"

class Category
{
private:
	unsigned id = 0;
	MyString name;
	MyString description;

	static unsigned nextId;
	static unsigned generateId();

public:
	Category();

	Category(const MyString name, const MyString& description);

	const unsigned getId() const;
	const MyString& getName() const;
	const MyString& getDescription() const;

 	void setName(const MyString& name);
	void setDescription(const MyString& descrription);
};