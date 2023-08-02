#pragma once
#include <ostream>

class MyString
{
public:
	MyString(const char* string);

	~MyString();

	// copy constructor
	MyString(const MyString& other);

	char& operator[](const unsigned int index) const;

	friend std::ostream& operator<<(std::ostream& stream, const MyString& string);

private:
	char* m_Buffer;
	unsigned long long m_Size;
};
