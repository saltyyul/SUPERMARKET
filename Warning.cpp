#include "./Warning.h"
#include <iostream>

void Warning::copyFrom(const Warning& other)
{
	senderName = other.senderName;
	description = other.description;
	points = other.points;
}

void Warning::free()
{

}

Warning::Warning()
{
	this->senderName = "";
	this->description = "";
	this->points = 0;
}

Warning::Warning(const MyString& sender, const MyString& description, const unsigned points)
	:senderName(sender), description(description), points(points)
{}

Warning::Warning(const Warning& other)
{
	copyFrom(other);
}

Warning& Warning::operator=(const Warning& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Warning::~Warning()
{
	free();
}

void Warning::printInfo() const
{
	std::cout << "Manager: " << senderName << std::endl;
	std::cout << "Description: " << description << std::endl;
	std::cout << "Warning points: " << points << std::endl;
}