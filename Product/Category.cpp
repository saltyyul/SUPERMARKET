#include "Category.h"
#include <iostream>

unsigned Category::nextId = 1;

unsigned Category::generateId()
{
	return nextId++;
}

Category::Category()
{

}

Category::Category(const MyString& name, const MyString& description)
{
	id = generateId();
	setName(name);
	setDescription(description);
}

const unsigned Category::getId() const
{
	return id;
}
 const MyString& Category::getName() const
{
	return name;
}
 const MyString& Category::getDescription() const
{
	return description;
}

void Category::setName(const MyString& name)
{
	if (name == "" || this->name == name)
	{
		std::cout << "Invalid category name" << std::endl;
		return;
	}
	this->name = name;
}

void Category::setDescription(const MyString& description)
{
	if (description == "" || this->description == description)
	{
		std::cout << "Invalid category description" << std::endl;
		return;
	}
	this->description = description;
}