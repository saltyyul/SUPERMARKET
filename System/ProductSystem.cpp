#include "ProductSystem.h"

#pragma warning (disable: 4996)

void ProductSystem::resizeProducts(SupermarketSystem& system, unsigned newCap)
{
	Product** newProducts = new Product * [newCap] {};

	for (size_t i = 0; i < system.prodcutCount; i++)
	{
		newProducts[i] = system.products[i];
	}

	delete[] system.products;
	system.products = newProducts;

	system.productCapacity = newCap;
}

void ProductSystem::resizeCategories(SupermarketSystem& system, unsigned newCap)
{
	Category** newCategories = new Category * [newCap] {};

	for (size_t i = 0; i < system.categoryCount; i++)
	{
		newCategories[i] = system.categories[i];
	}

	delete[] system.categories;
	system.categories = newCategories;

	system.categoryCapacity = newCap;
}

void ProductSystem::resizeGiftcards(SupermarketSystem& system, unsigned newCap)
{
	Giftcard** newGiftcards = new Giftcard * [newCap] {};

	for (size_t i = 0; i < system.giftCount; i++)
	{
		newGiftcards[i] = system.giftcards[i];
	}

	delete[] system.giftcards;
	system.giftcards = newGiftcards;

	system.giftCapacity = newCap;
}
void ProductSystem::listProducts(const SupermarketSystem& system)
{
	std::cout << "PRODUCTS: " << std::endl;

	for (size_t i = 0; i < system.prodcutCount; i++)
	{
		std::cout << "Id: " << system.products[i]->getId();
		std::cout << "Name: " << system.products[i]->getName();
		std::cout << "Category Id: " << system.products[i]->getCategoryId();

		if (dynamic_cast<ProductByUnit*>(system.products[i]))
		{
			std::cout << "Quantity: " << system.products[i]->getQuantity();
			std::cout << "Price By Unit: " << system.products[i]->getPrice();
		}
		else if (dynamic_cast<ProductByWeight*>(system.products[i]))
		{
			std::cout << "Quantity: " << system.products[i]->getQuantity();
			std::cout << "Price By Weight: " << system.products[i]->getPrice();
		}
	}
}

void ProductSystem::listProductsByCategory(const SupermarketSystem& system, const unsigned categoryId)
{
	std::cout << "PRODUCTS IN CATEGORY " << categoryId << " :" << std::endl;

	for (size_t i = 0; i < system.prodcutCount; i++)
	{
		if (!system.products[i])
		{
			continue;
		}
		if (system.products[i]->getCategoryId() == categoryId)
		{
			std::cout << "Id: " << system.products[i]->getId();
			std::cout << "Name: " << system.products[i]->getName();
			std::cout << "Category Id: " << system.products[i]->getCategoryId();

			if (dynamic_cast<ProductByUnit*>(system.products[i]))
			{
				std::cout << "Price By Unit: " << system.products[i]->getPrice();
			}
			else if (dynamic_cast<ProductByWeight*>(system.products[i]))
			{
				std::cout << "Price By Weight: " << system.products[i]->getPrice();
			}

			std::cout << "Available quantity: " << system.products[i]->getQuantity();
		}
		
	}
}

void ProductSystem::loadProducts(SupermarketSystem& system, const MyString& fileName)
{
	if (!system.currentUser || system.currentUser->getRole() != "manager")
	{
		std::cout << "You don't have access to this command." << std::endl;
		return;
	}

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

	char buff[Constants::MAX_BUFFER_SIZE];
	while (ifs.getline(buff, sizeof(buff)))
	{
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
			newProduct = new ProductByWeight(MyString(name), categoryId, price, quantity);
		}
		else
		{
			std::cout << "Invalid product type" << std::endl;
		}

		if (system.prodcutCount >= system.productCapacity)
		{
			resizeProducts(system, system.prodcutCount * 2);
		}
		system.products[system.prodcutCount++] = newProduct;
	}
	ifs.close();

	FeedSystem::addFeed(system, system.currentUser->getFullName(), "Loaded new products to the system.");
}

void ProductSystem::loadGiftcards(SupermarketSystem& system, const MyString& fileName)
{
	if (!system.currentUser || system.currentUser->getRole() != "manager")
	{
		std::cout << "You don't have access to this command." << std::endl;
		return;
	}

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

	char buff[Constants::MAX_BUFFER_SIZE];
	while (ifs.getline(buff, sizeof(buff)))
	{
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

		if (system.giftCount >= system.giftCapacity)
		{
			resizeGiftcards(system, system.giftCount * 2);
		}
		system.giftcards[system.giftCount++] = newGift;
	}
	ifs.close();

	FeedSystem::addFeed(system, system.currentUser->getFullName(), "Loaded new gift cards to the system.");
}
void ProductSystem::saveProducts(const SupermarketSystem& system, const MyString& fileName)
{
	if (fileName == "")
	{
		std::cout << "Save file for products.txt corrupted or missing" << std::endl;
		return;
	}
	std::ofstream ofs(fileName.c_str());
	if (!ofs.is_open())
	{
		std::cout << "Cannot open products.txt"<<std::endl;
		return;
	}

	for (size_t i = 0; i < system.prodcutCount; i++)
	{
		Product* product = system.products[i];

		const char* type = "none";
		if (dynamic_cast<ProductByUnit*>(product)) 
		{
			type = "unit";
		} 
		else if (dynamic_cast<ProductByWeight*>(product))
		{
			type = "weight";
		}

		ofs << type << "," << product->getName().c_str() << ","
			<< product->getCategoryId() << ","
			<< product->getPrice() << ","
			<< product->getQuantity() << "\n";
	}

	ofs.close();
}
void ProductSystem::saveGiftcards(const SupermarketSystem& system, const MyString& fileName)
{
	if (fileName == "")
	{
		std::cout << "Save file for giftcards.txt corrupted or missing" << std::endl;
		return;
	}
	std::ofstream ofs(fileName.c_str());
	if (!ofs.is_open())
	{
		std::cout << "Cannot open giftcards.txt"<<std::endl;
		return;
	}

	for (size_t i = 0; i < system.giftCount; i++)
	{
		Giftcard* giftcard = system.giftcards[i];

		const char* type = "none";
		if (dynamic_cast<SingleCategoryGiftcard*>(giftcard))
		{
			type = "single";
		}
		else if (dynamic_cast<MultipleCategoryGiftcard*>(giftcard))
		{
			type = "multiple";
		}
		else if (dynamic_cast<AllProductsGiftcard*>(giftcard))
		{
			type = "all";
		}

		ofs << type << ","
			<< giftcard->getCode() << ","
			<< giftcard->getDiscountValue() << "\n";
	}

	ofs.close();
}

void ProductSystem::addCategory(SupermarketSystem& system, const MyString& name, const MyString& description)
{
	if (!system.currentUser || system.currentUser->getRole() != "manager")
	{
		std::cout << "You don't have access to this command." << std::endl;
		return;
	}

	for (size_t i = 0; i < system.categoryCount; i++)
	{
		if (system.categories[i]->getName() == name)
		{
			std::cout << "Category already exists" << std::endl;
			return;
		}
	}

	if (system.categoryCount >= system.categoryCapacity)
	{
		resizeCategories(system, system.categoryCount * 2);
	}

	system.categories[system.categoryCount++] = new Category(name, description);
	std::cout << "Category added" << std::endl;
	FeedSystem::addFeed(system, system.currentUser->getFullName(), "Added new category: " + name);
}

void ProductSystem::deleteCategory(SupermarketSystem& system, unsigned categoryId)
{
	if (!system.currentUser || system.currentUser->getRole() != "manager")
	{
		std::cout << "You don't have access to this command." << std::endl;
		return;
	}

	for (size_t i = 0; i < system.categoryCount; i++)
	{
		if (system.categories[i]->getId() == categoryId)
		{
			delete system.categories[i];
			for (size_t j = i; j < system.categoryCount - 1; j++)
			{
				system.categories[j] = system.categories[j + 1];
			}
			system.categoryCount--;
			std::cout << "Category removed" << std::endl;
			FeedSystem::addFeed(system, system.currentUser->getFullName(), "Deleted category");
			return;
		}
	}
	std::cout << "No such category exists" << std::endl;
}
void ProductSystem::addProduct(SupermarketSystem& system, const MyString& type)
{
	if (!system.currentUser || system.currentUser->getRole() != "manager")
	{
		std::cout << "You don't have access to this command." << std::endl;
		return;
	}

	if (type != "unit" || type != "weight")
	{
		std::cout << "Invalid product type.\n";
		return;
	}

	char input[Constants::MAX_BUFFER_SIZE];
	MyString name, categoryName;
	double price = 0;
	double quantity = 0;

	std::cout << "Enter product name: ";
	std::cin >> input;
	name = input;

	std::cout << "Enter product category: ";
	std::cin >> input;
	categoryName = input;

	unsigned categoryIndex = -1;
	for (size_t i = 0; i < system.categoryCount; i++)
	{
		if (system.categories[i]->getName() == categoryName)
		{
			categoryIndex = i;
		}
	}

	if (categoryIndex <= 0)
	{
		std::cout << "Invalid category" << std::endl;
		return;
	}

	std::cout << "Enter price: \n";
	std::cin >> price;

	std::cout << "Enter quantity: \n";
	std::cin >> quantity;

	if (system.prodcutCount >= system.productCapacity) {
		resizeProducts(system, system.prodcutCount * 2);
	}

	Product* newProduct = nullptr;
	if (type == "unit")
	{
		newProduct = new ProductByUnit(name, system.categories[categoryIndex]->getId(), price, quantity);
	}
	else if (type == "weight")
	{
		newProduct = new ProductByWeight(name, system.categories[categoryIndex]->getId(), price, quantity);
	}
	
	system.products[system.prodcutCount++] = newProduct;
	std::cout << "Product " << newProduct->getName().c_str() << "added. \n";

	FeedSystem::addFeed(system, system.currentUser->getFullName(), "Added new product: " + name);
}

void ProductSystem::deleteProduct(SupermarketSystem& system, unsigned productId)
{
	if (!system.currentUser || system.currentUser->getRole() != "manager")
	{
		std::cout << "You don't have access to this command." << std::endl;
		return;
	}

	for (size_t i = 0; i < system.prodcutCount; ++i)
	{
		if (system.products[i]->getId() == productId)
		{
			delete system.products[i];
			for (size_t j = i; j < system.prodcutCount - 1; j++)
			{
				system.products[j] = system.products[j + 1];
			}
			system.prodcutCount--;
			std::cout << "Product removed" << std::endl;
			FeedSystem::addFeed(system, system.currentUser->getFullName(), "Deleted product");
			return;
		}
	}
	std::cout << "Product not found" << std::endl;
}