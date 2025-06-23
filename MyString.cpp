#include "MyString.h"
#include <cassert>

#pragma warning (disable : 4996)

void MyString::copyFrom(const MyString& other)
{
	size = other.size;
	capacity = other.capacity;
	data = new char[capacity] {};
	strcpy(data, other.data);
}

void MyString::free()
{
	delete[] data;
	data = nullptr;
	size = 0;
	capacity = 0;
}

void MyString::resize(unsigned newCap)
{
	char* newData = new char[newCap + 1] {};
	strcpy(newData, data);
	delete[] data;
	data = newData;
	capacity = newCap;
}

void MyString::moveFrom(MyString&& other)
{
	size = other.size;
	capacity = other.capacity;
	data = other.data;

	other.size = 0;
	other.capacity = 0;
	other.data = nullptr;
}

MyString::MyString()
{
	data = new char[1];
	data[0] = '\0';
}

MyString::MyString(const char* str)
{
	if (!data)
	{
		data = new char[1];
		data[0] = '\0';
	}
	
	size = strlen(str);
	capacity = size * 2;
	data = new char[capacity] {};
	strcpy(data, str);
}

MyString::MyString(const MyString& other)
{
	copyFrom(other);
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

MyString::MyString(MyString&& other) noexcept
{
	moveFrom(std::move(other));
}

MyString& MyString::operator=(MyString&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

MyString::~MyString()
{
	free();
}

const char* MyString::c_str() const
{
	return data;
}

const char* MyString::to_string(int number)
{
	static char buff[32];
	int index = 0;

	if (number == 0)
	{
		buff[index++] = '0';
	}
	else
	{
		while (number > 0)
		{
			int digit = number % 10;
			buff[index++] = (char)('0' + digit);
			number /= 10;
		}
	}

	buff[index] = '\0';

	int start = 0;
	int end = index - 1;

	while (start < end)
	{
		char temp = buff[start];
		buff[start] = buff[end];
		buff[end] = temp;

		start++;
		end--;
	}

	return buff;
}

size_t MyString::getLen() const 
{
	return size;
}

size_t MyString::getCapacity() const
{
	return capacity-1;
}

char& MyString::operator[](size_t index)
{
	assert(index < this->getLen());

	return data[index];
}

char MyString::operator[](size_t index) const
{
	assert(index < this->getLen());

	return data[index];

}

MyString& MyString::operator+=(const MyString& other)
{
	if (size + other.size + 1 > capacity)
	{
		resize((size+other.size)*2);
	}
		
	strncat(data, other.data, other.size);

	size += other.size;

	return *this;
}

MyString operator+(const MyString& lhs, const MyString& rhs)
{
	MyString result(lhs);
	result += rhs;

	return result;
}

std::istream& operator>>(std::istream& is, MyString& str)
{
	char buffer[1024];
	is >> buffer;

	size_t bufferLen = strlen(buffer);
	if (bufferLen >= str.capacity)
	{
		str.resize(bufferLen * 2);
	}

	strcpy(str.data, buffer);
	str.size = bufferLen;

	return is;
}

std::ostream& operator<<(std::ostream& os, const MyString& str)
{
	return os << str.c_str();
}

bool operator<(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator<=(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}
bool operator>=(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}

bool operator>(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) > 0;
}

bool operator==(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const MyString& lhs, const MyString& rhs)
{
	return !(lhs == rhs);
}