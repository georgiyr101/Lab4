#ifndef HUMAN_H
#define HUMAN_H

#include <iostream>
#include "String.h"

enum SearchParams
{
	LAST_NAME, FIRST_NAME, BIRTH_YEAR, ALL_PARAMS
};

class Human
{
protected:
	String firstName = "";
	String lastName = "";
	int birthYear = 0;
private:
	static SearchParams currentSearchParams;
public:
	Human() {}		
	Human(const String& firstName, const String& lastName, int birthYear)
	{
		this->firstName = firstName;
		this->lastName = lastName;
		this->birthYear = birthYear;
	}
	virtual ~Human(){}
	Human& operator=(const Human& other);
	bool operator==(const Human& other) const;
	bool operator<(const Human& other) const;

	String getFirstName() const;
	String getLastName() const;
	int getBirthYear() const;

	void setFirstName(const String& first);
	void setLastName(const String& last);
	void setBirthYear(int year);
	static void setSearchParams(SearchParams params);

	virtual void printHeader() const = 0;
	virtual void printInfo() const = 0;

	virtual char editMenu() const = 0;
	virtual void editFields() = 0;

	friend ostream& operator << (ostream& os, const Human& h);
	friend istream& operator >> (istream& is, Human& h);



};


#endif