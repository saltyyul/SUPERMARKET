#pragma once
#include <istream>

class MyString
{
private:
	char* data = nullptr;
	size_t size;
	size_t capacity;

	void copyFrom(const MyString& other);
	void free();
	void resize(unsigned newCap);
	void moveFrom(MyString&& other);
	
public:
	MyString();
	MyString(const char* str);

	MyString(const MyString& other);
	MyString& operator=(const MyString& other);

	MyString(MyString&& other) noexcept;
	MyString& operator=(MyString&& other) noexcept;

	~MyString();

	const char* c_str() const;
	static const char* to_string(int number);

	size_t getLen() const;
	size_t getCapacity() const;

	char& operator[](size_t index);
	char operator[](size_t index) const;

	MyString& operator+=(const MyString& other);

	friend MyString operator+(const MyString& lhs, const MyString& rhs);
	friend std::istream& operator>>(std::istream& is, MyString& str);
};

std::ostream& operator<<(std::ostream& os, const MyString& str);
bool operator<(const MyString& lhs, const MyString& rhs);
bool operator<=(const MyString& lhs, const MyString& rhs);
bool operator>=(const MyString& lhs, const MyString& rhs);
bool operator>(const MyString& lhs, const MyString& rhs);
bool operator==(const MyString& lhs, const MyString& rhs);
bool operator!=(const MyString& lhs, const MyString& rhs);