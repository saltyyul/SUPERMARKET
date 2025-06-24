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
