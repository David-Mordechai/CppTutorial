#include "MyString.h"

MyString::MyString(const char* string)
{
	m_Size = strlen(string);
	m_Buffer = new char[m_Size + 1];
	memcpy(m_Buffer, string, m_Size);
	m_Buffer[m_Size] = 0; // adding null termination
}

MyString::~MyString()
{
	delete[] m_Buffer;
}

MyString::MyString(const MyString& other) : m_Size(other.m_Size)
{
	m_Buffer = new char[m_Size + 1];
	memcpy(m_Buffer, other.m_Buffer, m_Size + 1);
}

char& MyString::operator[](const unsigned index) const
{
	return m_Buffer[index];
}
