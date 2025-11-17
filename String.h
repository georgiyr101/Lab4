#ifndef STRING_H
#define STRING_H

#include <iostream>
#include <cstring>
using namespace std;

class String
{
private:
	char* str = nullptr;
	int length = 0;
public:
	String() {}
	String(const char* s)
	{
		this->length = strlen(s);
		this->str = new char[length + 1];
		strcpy(this->str, s);
	}
	String(const String& other)
	{
		this->length = other.length;
		this->str = new char[length + 1];
		strcpy(this->str, other.str);
	}
	~String()
	{
		delete[] str;
	}

	String& operator=(const String& other);


	bool operator==(const String& other) const;

	bool operator!=(const String& other) const;

	bool operator < (const String& other) const;

	bool operator > (const String& other) const;


	String& operator+=(const String& other);


	String operator+(const String& other);

	char& operator[](int index);

	String operator()(int start, int end);

	friend ostream& operator<<(ostream& os, const String& s);
	friend istream& operator>>(istream& is, String& s);
};



#endif