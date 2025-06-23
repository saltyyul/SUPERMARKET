#include "SupermarketSystem.h"
#include <iostream>

#pragma warning (disable: 4996)

const unsigned MAX_BUFFER_SIZE = 1024;

struct SupermarketSystem::Transaction
{
	unsigned id;
	MyString name;
	unsigned categoryId;
	double price;
	double quantity;
	double total;

	Transaction() = default;

	Transaction(unsigned id, const MyString& name, unsigned categoryId,
		double price, double quantity)
		:id(id), name(name), categoryId(categoryId), price(price), quantity(quantity)
	{
		total = price * quantity;
	}
};

void SupermarketSystem::writeReceipt(unsigned cashierId, const Transaction* items, size_t count, double totalSum)
{
	const char* idStr = MyString::to_string(nextTransactionId);
	char fileName[MAX_BUFFER_SIZE];
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
	char dateBuff[MAX_BUFFER_SIZE];
	strftime(dateBuff, sizeof(dateBuff), "%Y-%m-%d %H:%M:%S", localTime);
	ofs << "RECEIPT \n";
	ofs << "TRANSACTION_ID: " << nextTransactionId << "\n";

	if (!currentUser || currentUser->getId()!=cashierId)
	{
		std::cout << "Invalid user" << std::endl;
		return;
	}

	const char* cashierIdStr = MyString::to_string(cashierId);
	ofs << "CASHIER_ID: " << cashierIdStr << "\n";
	ofs << dateBuff << "\n";
	ofs << "-------------------------\n";

	for (size_t i = 0; i < count; i++)
	{
		ofs << items[i].name.c_str() << "\n";
		ofs << items[i].quantity << "*" << items[i].price << " - " << items[i].total << "\n";
		ofs << "###\n";
	}

	ofs << "TOTAL: " << totalSum << "\n";
	ofs.close();
}

void SupermarketSystem::sell()
{
	if (!currentUser || currentUser->getRole() != "Cashier")
	{
		std::cout << "You don't have access to this command." << std::endl;
		return;
	}

	size_t itemCount = 0;
	size_t itemCapacity = 0;
	Transaction* items = new Transaction[itemCapacity];
	double totalSum = 0;

	char input[MAX_BUFFER_SIZE];
	while (true)
	{
		std::cout << "Enter product ID to sell. Enter END to end the transaction: " << std::endl;
		std::cin >> input;

		if (strcmp(input, "end") == 0) break;
		unsigned id = atoi(input);

		Product* product = nullptr;
		for (size_t i = 0; i < prodcutCount; i++)
		{
			if (products[i]->getId() == id)
			{
				product = products[i];
				break;
			}
		}

		if (!product)
		{
			std::cout << "Invalid product" << std::endl;
			return;
		}

		std::cout << "Enter quantity: " << std::endl;
		double quantity;
		std::cin >> quantity;
		if (!product->sell(quantity))
		{
			continue;
		}

		if (itemCount >= itemCapacity)
		{
			itemCapacity = itemCount * 2;
			Transaction* newItems = new Transaction[itemCapacity];
			for (size_t i = 0; i < itemCount; i++)
			{
				newItems[i] = items[i];
			}
			delete[] items;
			items = newItems;
		}

		items[itemCount++] = Transaction(product->getId(), product->getName(), 
			product->getCategoryId(), product->getPrice(), quantity);
		totalSum += items[itemCount - 1].total;
	}

	std::cout << "Add voucher: (Y/N) ?" << std::endl;
	std::cin >> input;
	if (strcmp(input, "y") == 0)
	{
		std::cout << "Enter voucher:" << std::endl;
		std::cin >> input;

		for (size_t i = 0; i < giftCount; i++)
		{
			if (strcmp(giftcards[i]->getCode().c_str(), input) == 0) 
			{
				totalSum -= giftcards[i]->getDiscountValue();
				if (totalSum < 0) totalSum = 0;
				std::cout << "Discount applied!" << std::endl;
				break;
			}
		}
	}
	std::cout << "Transaction complete!" << std::endl;

	writeReceipt(currentUser->getId(), items, itemCount, totalSum);
	nextTransactionId++;
	delete[] items;

	Cashier* cashier = dynamic_cast<Cashier*>(currentUser);
	if (cashier)
	{
		cashier->addTransaction();
		if (cashier->getTransactionCount() % 3 == 0)
		{
			cashier->removeOldestWarning();
		}
	}
}

void SupermarketSystem::resizeUsers(unsigned newCap)
{
	User** newUsers = new User * [newCap]{};

	for (size_t i = 0; i < userCount; i++)
	{
		newUsers[i] = users[i];
	}

	delete[] users;
	newUsers = users;

	userCapacity = newCap;
}

void SupermarketSystem::resizeCategories(unsigned newCap) 
{
	Category** newCategories = new Category * [newCap]{};

	for (size_t i = 0; i < categoryCount; i++)
	{
		newCategories[i] = categories[i];
	}

	delete[] categories;
	newCategories = categories;

	categoryCapacity = newCap;
}

void SupermarketSystem::resizeProducts(unsigned newCap)
{
	Product** newProducts = new Product * [newCap]{};

	for (size_t i = 0; i < prodcutCount; i++)
	{
		newProducts[i] = products[i];
	}

	delete[] products;
	newProducts = products;

	productCapacity = newCap;
}

void SupermarketSystem::resizeGiftcards(unsigned newCap)
{
	Giftcard** newGiftcards = new Giftcard * [newCap] {};

	for (size_t i = 0; i < giftCount; i++)
	{
		newGiftcards[i] = giftcards[i];
	}

	delete[] giftcards;
	newGiftcards = giftcards;

	giftCapacity = newCap;
}

SupermarketSystem::SupermarketSystem()
{
	userCapacity = categoryCapacity = productCapacity = 8;

	users = new User * [userCapacity];
	categories = new Category * [categoryCapacity];
	products = new Product * [productCapacity];
}

SupermarketSystem:: ~SupermarketSystem()
{
	userCount = categoryCount = prodcutCount = 0;
}

void SupermarketSystem::login(unsigned id, const MyString& password)
{
	for (size_t i = 0; i < userCount; i++)
	{
		if (id == users[i]->getId() && password == users[i]->getPass()) 
		{
			currentUser = users[i];
			std::cout << "User " << currentUser->getFullName()
				<<" with ID: "<< currentUser->getId()
				<< " has been logged into this system!" << std::endl;
		}
	}

	std::cout << "Incorrect id/password!" << std::endl;
}

void SupermarketSystem::logout() 
{
	currentUser = nullptr;
	std::cout << "You have logged out" << std::endl;
}

void SupermarketSystem::listUserData() const
{
	if (!currentUser)
	{
		std::cout << "Log in to have access to this function" << std::endl;
		return;
	}

	currentUser->printInfo();
}

void SupermarketSystem::listWorkers() const
{
	if (!currentUser)
	{
		std::cout<<"Log in to have access to this function" << std::endl;
		return;
	}
	for (size_t i = 0; i < userCount; i++)
	{
		if (users[i]->getRole() == "Cashier" || users[i]->getRole() == "Manager")
		{
			users[i]->printInfo();
		}
		std::cout << "------------" << std::endl;
	}
}

void SupermarketSystem::listProducts() const
{
	std::cout << "PRODUCTS: " << std::endl;

	for (size_t i = 0; i < prodcutCount; i++)
	{
		std::cout << "Id: " << products[i]->getId();
		std::cout << "Name: " << products[i]->getName();
		std::cout << "Category Id: " << products[i]->getCategoryId();

		if (dynamic_cast<ProductByUnit*>(products[i]))
		{
			std::cout << "Quantity: " << products[i]->getQuantity();
			std::cout << "Price By Unit: " << products[i]->getPrice();
		}
		else if (dynamic_cast<ProductByWeight*>(products[i]))
		{
			std::cout << "Quantity: " << products[i]->getQuantity();
			std::cout << "Price By Weight: " << products[i]->getPrice();
		}
	}
}

void SupermarketSystem::listProductsByCategory(const unsigned categoryId) const
{
	std::cout << "PRODUCTS IN CATEGORY "<< categoryId << " :" << std::endl;

	for (size_t i = 0; i < prodcutCount; i++)
	{
		if(products[i]->getCategoryId() == categoryId)

		std::cout << "Id: " << products[i]->getId();
		std::cout << "Name: " << products[i]->getName();
		std::cout << "Category Id: " << products[i]->getCategoryId();

		if (dynamic_cast<ProductByUnit*>(products[i]))
		{
			std::cout << "Price By Unit: " << products[i]->getPrice();
		}
		else if (dynamic_cast<ProductByWeight*>(products[i]))
		{
			std::cout << "Price By Weight: " << products[i]->getPrice();
		}

		std::cout << "Available quantity: " << products[i]->getQuantity();
	}
}

void SupermarketSystem::loadProducts(const MyString& fileName)
{
	if (fileName == "")
	{
		std::cout << "Invalid file name" << std::endl;
		return;
	}

	std::ifstream ifs(fileName.c_str());
	if (!ifs.is_open())
	{
		std::cout << "Cannot open file!" << std::endl;
		return;
	}

	char buff[MAX_BUFFER_SIZE];
	while (!ifs.eof())
	{
		ifs.getline(buff, sizeof(buff));
		char* type = strtok(buff, ",");
		char* name = strtok(nullptr, ",");
		char* categoryStr = strtok(nullptr, ",");
		char* priceStr = strtok(nullptr, ",");
		char* quantityStr = strtok(nullptr, ",");

		if (!type || !name || !categoryStr || !priceStr || !quantityStr)
		{
			std::cout << "Invalid arguments, one may be missing" << std::endl;
			return;
		}

		unsigned categoryId = atoi(categoryStr);
		double price = atof(priceStr);
		double quantity = atof(quantityStr);

		Product* newProduct = nullptr;
		if (strcmp(type, "unit") == 0)
		{
			newProduct = new ProductByUnit(MyString(name), categoryId, price, quantity);
		}
		else if (strcmp(type, "weight") == 0)
		{
			newProduct = new ProductByUnit(MyString(name), categoryId, price, quantity);
		}
		else
		{
			std::cout << "Invalid product type" << std::endl;
		}

		if (prodcutCount >= productCapacity)
		{
			resizeProducts(prodcutCount * 2);
		}
		products[prodcutCount++] = newProduct;
	}
	ifs.close();
}

void SupermarketSystem::loadGiftcards(const MyString& fileName)
{
	if (fileName == "")
	{
		std::cout << "Invalid file name" << std::endl;
		return;
	}

	std::ifstream ifs(fileName.c_str());
	if (!ifs.is_open())
	{
		std::cout << "Cannot open file!" << std::endl;
		return;
	}

	char buff[MAX_BUFFER_SIZE];
	while (!ifs.eof())
	{
		ifs.getline(buff, sizeof(buff));
		char* type = strtok(buff, ",");
		char* code = strtok(nullptr, ",");
		char* discountValueStr = strtok(nullptr, ",");
	
		if (!type || !code || !discountValueStr)
		{
			std::cout << "Invalid arguments, one may be missing" << std::endl;
			return;
		}

		double discountValue = atof(discountValueStr);

		Giftcard* newGift = nullptr;
		if (strcmp(type, "single") == 0)
		{
			newGift = new SingleCategoryGiftcard(code, discountValue);
		}
		else if (strcmp(type, "multiple") == 0)
		{
			newGift = new MultipleCategoryGiftcard(code, discountValue);
		}
		else if (strcmp(type, "all") == 0)
		{
			newGift = new AllProductsGiftcard(code, discountValue);
		}
		else 
		{
			std::cout << "Invalid product type" << std::endl;
		}

		if (giftCount >= giftCapacity)
		{
			resizeGiftcards(giftCount * 2);
		}
		giftcards[giftCount++] = newGift;
	}
	ifs.close();
}

void SupermarketSystem::warnCashier(const MyString& name)
{
	if (currentUser->getRole() != "Manager")
	{
		std::cout << "You don't have access to this command." << std::endl;
		return;
	}

	for (size_t i = 0; i < userCount; i++)
	{
		if (users[i]->getRole() == "Cashier" && users[i]->getFullName() == name)
		{
			std::cout << "Warning description: " << std::endl;
			char input[MAX_BUFFER_SIZE];
			std::cin.ignore();
			std::cin.getline(input, sizeof(input));


			std::cout << "Warning severity points:" << std::endl;
			unsigned points;
			std::cin >> points;

			Warning w(currentUser->getFullName(), MyString(input), points);
			Cashier* cashier = dynamic_cast<Cashier*>(users[i]);
			cashier->addWarning(w);

			std::cout << "Warning added" << std::endl;
			return;
		}
	}
	std::cout << "Cannot find cashier " << name << std::endl;
}

void SupermarketSystem::listWarnedCashiers(unsigned points) const
{
	std::cout << "Warned cashiers with over "<< points <<" points:" << std::endl;
	for (size_t i = 0; i < userCount; i++)
	{
		if (users[i]->getRole() == "Cashier")
		{
			Cashier* cashier = dynamic_cast<Cashier*>(users[i]);
			if (cashier->getWarningPoints() >= points)
			{
				cashier->printInfo();
			}
		}
	}
}