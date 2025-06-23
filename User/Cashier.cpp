#include "Cashier.h"
#include "../Warning.h"
#include "../MyString.h"
#include <iostream>

void Cashier::copyFrom(const Cashier& other)
{
	transactionCount = other.transactionCount;
	warningCount = other.warningCount;
	warningCapacity = other.warningCapacity;
	approved = other.approved;

	warnings = new Warning[warningCapacity]{};
	for (size_t i = 0; i < warningCount; i++)
	{
		warnings[i] = other.warnings[i];
	}
}
void Cashier::free()
{
	delete[] warnings;
	warnings = nullptr;
	warningCount = 0;
	warningCapacity = 0;
	approved = false;
}
void Cashier::resize(size_t newCap)
{
	Warning* newWarnings = new Warning[newCap]{};

	for (size_t i = 0; i < warningCount; i++)
	{
		newWarnings[i] = warnings[i];
	}
	delete[] warnings;
	warnings = newWarnings;

	warningCapacity = newCap;
}

Cashier::Cashier(const MyString& fn, const MyString& ln, const MyString& phoneNum,
	const unsigned age, const MyString& pass)
	:User(generateId(), fn, ln, phoneNum, age, pass)
{
	approved = false;
}

Cashier::Cashier(const Cashier& other):User(other)
{
	copyFrom(other);
}

Cashier& Cashier::operator=(const Cashier& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Cashier::~Cashier()
{
	free();
}

void Cashier::printInfo() const
{
	User::printInfo();
	std::cout << "Role: " << getRole() << std::endl;
	std::cout << "Transactions count: " << transactionCount << std::endl;
	std::cout << "Warnings: " << std::endl;

	for (size_t i = 0; i < warningCount; i++)
	{
		warnings[i].printInfo();
	}
}

const MyString& Cashier::getRole() const
{
	return "cashier";
}

int Cashier::getTransactionCount() const
{
	return transactionCount;
}

int Cashier::getWarningPoints() const
{
	int sum = 0;
	for (size_t i = 0; i < warningCount; i++)
	{
		sum += warnings[i].getPoints();
	}

	return sum;
}

bool Cashier::checkIfApproved() const
{
	return approved;
}

void Cashier::addWarning(const Warning& warning)
{
	if (warningCount >= warningCapacity)
	{
		resize(warningCount * 2);
	}

	warnings[warningCount++] = warning;
}
void Cashier::addTransaction()
{
	++transactionCount;
}
void Cashier::removeOldestWarning()
{
	if (warningCount == 0) return;
	for (size_t i = 1; i < warningCount; i++)
	{
		warnings[i - 1] = warnings[i];
	}
	warningCount--;
}

void Cashier::setApproval()
{
	this->approved = true;
}
