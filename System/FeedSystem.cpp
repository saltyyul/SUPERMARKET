#include "FeedSystem.h"

void FeedSystem::resizeFeed(SupermarketSystem& system, unsigned newCap)
{
	Feed** newFeed = new Feed * [newCap] {};

	for (size_t i = 0; i < system.feedCount; i++)
	{
		newFeed[i] = system.feed[i];
	}

	delete[] system.feed;
	system.feed = newFeed;

	system.feedCapacity = newCap;
}

void FeedSystem::listFeed(const SupermarketSystem& system)
{
	if (system.feedCount == 0)
	{
		std::cout << "Feed is empty" << std::endl;
		return;
	}

	for (size_t i = 0; i < system.feedCount; i++)
	{
		system.feed[i]->printFeedInfo();
	}
}

void FeedSystem::addFeed(SupermarketSystem& system, const MyString& author, const MyString& description)
{
	if (system.feedCount >= system.feedCapacity)
	{
		resizeFeed(system, system.feedCount * 2);
	}

	MyString date = system.getCurrentDate();
	system.feed[system.feedCount++] = new Feed(author, description, date);
}

void FeedSystem::loadFeed(SupermarketSystem& system, const MyString& fileName)
{
	if (fileName == "")
	{
		std::cout << "Save file for feed.txt corrupted or missing" << std::endl;
		return;
	}

	std::ifstream ifs(fileName.c_str());
	if (!ifs.is_open())
	{
		//std::cout << "Cannot open feed.txt" << std::endl;
		return;
	}

	char buff[Constants::MAX_BUFFER_SIZE];
	MyString author, desc, date;

	while (ifs.getline(buff, sizeof(buff))) 
	{
		if (strcmp(buff, "start") == 0) 
		{
			author = "";
			desc = "";
			date = "";
		}
		else if (strncmp(buff, "author,", 7) == 0)
		{
			author = MyString(buff + 7);
		}
		else if (strncmp(buff, "desc,", 5) == 0)
		{
			desc = MyString(buff + 5);
		}
		else if (strncmp(buff, "date,", 5) == 0)
		{
			date = MyString(buff + 5);
		}
		else if (strcmp(buff, "end") == 0)
		{
			if (system.feedCount >= system.feedCapacity)
			{
				resizeFeed(system, system.feedCapacity * 2);
			}
			system.feed[system.feedCount++] = new Feed(author, desc, date);
		}
	}
	ifs.close();
}

void FeedSystem::saveFeed(const SupermarketSystem& system, const MyString& fileName)
{
	if (fileName == "") 
	{
		std::cout << "Save file for feed.txt corrupted or missing" << std::endl;
		return;
	}

	std::ofstream ofs(fileName.c_str());
	if (!ofs.is_open()) 
	{
		std::cout << "Cannot open feed.txt" << std::endl;
		return;
	}

	for (size_t i = 0; i < system.feedCount; i++) 
	{
		Feed* feed = system.feed[i];

		ofs << "start\n";
		ofs << "author," << feed->getAuthor().c_str() << "\n";
		ofs << "desc," << feed->getDescription().c_str() << "\n";
		ofs << "date," << feed->getDate().c_str() << "\n";
		ofs << "end\n";
	}

	ofs.close();
}
