#include "String.h"


String& String::operator=(const String& other)
{
	if (this != &other)
	{
		delete[] str;
		if (other.str != nullptr)
		{
			this->length = other.length;
			this->str = new char[length + 1];
			strcpy(str, other.str);
		}
		else
		{
			this->str = nullptr;
			this->length = 0;
		}

	}
	return *this;
}

bool String::operator==(const String& other) const
{
	return strcmp(str, other.str) == 0;
}

bool String::operator!=(const String& other) const
{
	return !(*this == other);
}

bool String::operator < (const String& other) const
{
	return strcmp(str, other.str) < 0;
}

bool String::operator > (const String& other) const
{
	return strcmp(str, other.str) > 0;
}

String& String::operator+=(const String& other)
{
	if (other.length == 0) {
		return *this;
	}
	int newLength = length + other.length;
	char* temp = new char[newLength + 1];

	if (length > 0) {
		memcpy(temp, str, length);
	}
	memcpy(temp + length, other.str, other.length + 1);
	delete[] str;
	str = temp;
	length = newLength;
	return *this;
}

String String::operator+(const String& other)
{
	String result(*this);
	result += other;
	return result;
}

char& String::operator[](int index)
{
	if (index < 0 || index >= length) throw "Index out of range";
	return str[index];
}

String String::operator()(int start, int end)
{
	if (start < 0 || end >= length || start > end) throw "Invalid substring range";
	String result;
	result.length = end - start + 1;
	result.str = new char[result.length + 1];
	strncpy(result.str, this->str + start, result.length);
	result.str[result.length] = '\0';
	return result;
}

ostream& operator<<(ostream& os, const String& s)
{
	if (s.str != nullptr) {
		os << s.str;
	}
	return os;
}

istream& operator>>(istream& is, String& s)
{
	char buffer[100];
	is.getline(buffer, 100);
	s = String(buffer);
	return is;
}