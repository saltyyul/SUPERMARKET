#pragma once
#include "User.h"
#include "Warning.h"

class Cashier : public User
{
private:
	int transactionCount = 0;
	Warning* warnings = nullptr;
	int warningCount = 0;
	int warningCapacity = 0;
	bool approved = false;

	void copyFrom(const Cashier& other);
	void free();
	void resize(size_t newCap);


public:
	Cashier(const MyString& fn, const MyString& ln,const MyString& phoneNum,
		const unsigned age, const MyString& pass);

	Cashier(const Cashier& other);
	Cashier& operator=(const Cashier& other);

	~Cashier();

	void printInfo() const override;

	const MyString& getRole() const override;
	int getTransactionCount() const;
	int getWarningPoints() const;
	bool checkIfApproved() const;

	void addWarning(const Warning& warning);
	void addTransaction();
	void removeOldestWarning();
	void setApproval();
};