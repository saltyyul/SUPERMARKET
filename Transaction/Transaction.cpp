#include "Transaction.h"

#pragma warning (disable: 4996)
unsigned Transaction::nextId = 0;

unsigned Transaction::generateId()
{
	return nextId++;
}

void Transaction::copyFrom(const Transaction& other)
{
	transactionId = other.transactionId;
	total = other.total;
	date = other.date;
	cashierId = other.cashierId;

	productCount = other.productCount;
	productCapacity = other.productCapacity;
	for (size_t i = 0; i < productCount; i++)
	{
		products[i] = other.products[i];
		quantities[i] = other.quantities[i];
	}
}

void Transaction::resize(unsigned newCapacity)
{
	Product** newProducts = new Product * [newCapacity] {nullptr};
	double* newQuantitites = new double[newCapacity];
	for (size_t i = 0; i < productCount; i++)
	{
		newProducts[i] = products[i];
		newQuantitites[i] = quantities[i];
	}
	delete[] products;
	delete[] quantities;

	products = newProducts;
	quantities = newQuantitites;
	productCapacity = newCapacity;
}

void Transaction::free()
{
	delete[] products;
	delete[] quantities;
}

Transaction::Transaction(unsigned cashierId, const MyString& date)
	: transactionId(generateId()), cashierId(cashierId), date(date)
{
	productCapacity = 8;
	products = new Product * [productCapacity];
	quantities = new double[productCapacity];
}

Transaction::Transaction(const Transaction& other)
{
	copyFrom(other);
}

Transaction& Transaction::operator= (const Transaction& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return*this;
}
Transaction::~Transaction()
{
	free();
}

void Transaction::addProduct(Product* product, double quantity)
{
	if (productCount >= productCapacity)
	{
		resize(productCount * 2);
	}
	products[productCount] = product;
	quantities[productCount] = quantity;
	total += product->getPrice() * quantity;
	productCount++;
}

void Transaction::applyDiscount(double value)
{
	total -= value;
	if (total > 0) total = 0;
}

void Transaction::printReceipt() const
{
	const char* idStr = MyString::to_string(nextId);
	char fileName[Constants::MAX_BUFFER_SIZE];
	strcpy(fileName, "receipt_");
	strcat(fileName, idStr);
	strcat(fileName, ".txt");

	std::ofstream ofs(fileName);
	if (!ofs.is_open())
	{
		std::cout << "Cannot open file" << std::endl;
		return;
	}

	time_t curr = time(0);
	tm* localTime = localtime(&curr);
	char dateBuff[Constants::MAX_BUFFER_SIZE];
	strftime(dateBuff, sizeof(dateBuff), "%Y-%m-%d %H:%M:%S", localTime);
	ofs << "RECEIPT \n";
	ofs << "TRANSACTION_ID: " << nextId << "\n";
	const char* cashierIdStr = MyString::to_string(cashierId);
	ofs << "CASHIER_ID: " << cashierIdStr << "\n";
	ofs << dateBuff << "\n";
	ofs << "-------------------------\n";

	for (size_t i = 0; i < productCount; i++)
	{
		ofs << products[i]->getName().c_str() << "\n";
		ofs << quantities[i] << "*" << products[i]->getPrice() << " - " << quantities[i]* products[i]->getPrice() << "\n";
		ofs << "###\n";
	}

	ofs << "TOTAL: " << total<< "\n";
	ofs.close();
}

void Transaction::printInfo() const
{
	std::cout << "Transaction ID: " << transactionId << std::endl;
	std::cout << "Total: " << total << std::endl;
	std::cout << "Date: " << date.c_str() << std::endl;
}

unsigned Transaction::getCashierId() const
{
	return cashierId;
}

MyString Transaction::getDate() const
{
	return date;
}

unsigned Transaction::getProductCount() const
{
	return productCount;
}

Product* Transaction::getProduct(unsigned index) const
{
	if (index >= productCount)
	{
		return nullptr;
	}
	return products[index];
}

double Transaction::getQuantity(unsigned index) const
{
	if (index >= productCount)
	{
		return 0.0;
	}
	return quantities[index];
}

double Transaction::getTotal() const
{
	return total;
}
