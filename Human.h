#ifndef HUMAN_H
#define HUMAN_H

#include <iostream>
#include <string>
using namespace std;

class Human
{
protected:
	string firstName = "";
	string lastName = "";
	int birthYear = 0;
public:
	Human() {}		
	Human(const string& firstName, const string& lastName, int birthYear)
	{
		this->firstName = firstName;
		this->lastName = lastName;
		this->birthYear = birthYear;
	}
	virtual ~Human(){}
	Human& operator=(const Human& other);

	string getFirstName() const;
	string getLastName() const;
	int getBirthYear() const;

	void setFirstName(const string& first);
	void setLastName(const string& last);
	void setBirthYear(int year);

	virtual void printHeader() const = 0;
	virtual void printInfo() const = 0;

	virtual char editMenu() const = 0;
	virtual void editFields() = 0;

	virtual void saveTextRecord(ostream& os) const;
	virtual void saveBinaryRecord(ostream& os) const;

	virtual void loadFromText(istream& is);
	virtual void loadFromBinary(istream& is);

	friend ostream& operator << (ostream& os, const Human& h);
	friend istream& operator >> (istream& is, Human& h);



};


#endif