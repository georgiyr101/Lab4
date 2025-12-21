#ifndef TEACHER_H
#define TEACHER_H

#include "Human.h"

#define MAX_PUBLICATIONS 10

class Teacher : virtual public Human
{
protected:
	string position = "";
	string specialty = "";
	string scientificPublications[MAX_PUBLICATIONS];
	int publicationsCount = 0;
public:
	Teacher() {}
	Teacher(string firstName, string lastName, int birthYear, string position, string specialty): Human(firstName, lastName, birthYear), position(position), specialty(specialty), publicationsCount(0) {}
	virtual ~Teacher() {};
	Teacher& operator=(const Teacher& other);

	string getPosition() const;
	string getSpecialty() const;
	int getPublicationsCount() const;
	string getScientificPublication(int index) const;

	void setPosition(const string& position);
	void setSpecialty(const string& specialty);
	bool addScientificPublication(const string& publication);
	bool setScientificPublication(int index, const string& publication);

	virtual char editMenu() const override;
	virtual void editFields() override;

	virtual void printHeader() const override;
	virtual void printInfo() const override;

	virtual void saveTextRecord(ostream& os) const override;
	virtual void saveBinaryRecord(ostream& os) const override;

	virtual void loadFromText(istream& is) override;
	virtual void loadFromBinary(istream& is) override;

	friend ostream& operator << (ostream& os, const Teacher& teacher);
	friend istream& operator >> (istream& is, Teacher& teacher);



};


#endif