#pragma once
#include "MyString.h"
#include <iostream>

class Feed
{
private:
	MyString author;
	MyString description;
	MyString date;

	void copyFrom(const Feed& other)
	{
		author = other.author;
		description = other.description;
		date = other.date;
	}

public:
	Feed() = default;

	Feed(const MyString& author, const MyString& desc, const MyString& date)
		:author(author), description(desc), date(date)
	{}

	Feed(const Feed& other)
	{
		copyFrom(other);
	}

	Feed& operator=(const Feed& other)
	{
		if (this != &other)
		{
			copyFrom(other);
		}

		return *this;
	}

	~Feed() = default;

	const MyString& getAuthor() const { return author; }
	const MyString& getDescription() const { return description; }
	const MyString& getDate() const { return date; }

	void printFeedInfo() const
	{
		std::cout << author << ": " << description << " (" << date << ")" << std::endl;
	}
};