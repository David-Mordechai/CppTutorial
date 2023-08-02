#pragma once
#include <iostream>

#include "MyString.h"

inline std::ostream& operator<<(std::ostream& stream, const MyString& string)
{
	stream << string.m_Buffer;
	return stream;
}

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