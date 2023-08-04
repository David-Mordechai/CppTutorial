#pragma once
#include <iostream>

// MyString h file
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

inline MyString::MyString(const char* string)
{
	m_Size = strlen(string);
	m_Buffer = new char[m_Size + 1];
	memcpy(m_Buffer, string, m_Size);
	m_Buffer[m_Size] = 0; // adding null termination
}
// end MyString h file

// MyString cpp file
inline MyString::~MyString()
{
	delete[] m_Buffer;
}

inline MyString::MyString(const MyString& other) : m_Size(other.m_Size)
{
	m_Buffer = new char[m_Size + 1];
	memcpy(m_Buffer, other.m_Buffer, m_Size + 1);
}

inline char& MyString::operator[](const unsigned index) const
{
	return m_Buffer[index];
}

inline std::ostream& operator<<(std::ostream& stream, const MyString& string)
{
	stream << string.m_Buffer;
	return stream;
}
// end MyString cpp file

void inline PrintString(const MyString& string)
{
	std::cout << string << std::endl;
}

void inline CopyingAndCopyConstructors()
{
	const MyString string1 = "David";
	const MyString string2 = string1;

	string2[0] = 'd';

	PrintString(string1);
	PrintString(string2);
}