#ifndef TEACHER_H
#define TEACHER_H

#include "Human.h"

#define MAX_PUBLICATIONS 10

class Teacher : virtual public Human
{
protected:
	String position = "";
	String specialty = "";
	String scientificPublications[MAX_PUBLICATIONS];
	int publicationsCount = 0;
public:
	Teacher() {}
	Teacher(String firstName, String lastName, int birthYear, String position, String specialty): Human(firstName, lastName, birthYear), position(position), specialty(specialty), publicationsCount(0) {}
	virtual ~Teacher() {};
	Teacher& operator=(const Teacher& other);

	String getPosition() const;
	String getSpecialty() const;
	int getPublicationsCount() const;
	String getScientificPublication(int index) const;

	void setPosition(const String& position);
	void setSpecialty(const String& specialty);
	bool addScientificPublication(const String& publication);
	bool setScientificPublication(int index, const String& publication);

	virtual char editMenu() const override;
	virtual void editFields() override;

	virtual void printHeader() const override;
	virtual void printInfo() const override;

	friend ostream& operator << (ostream& os, const Teacher& teacher);
	friend istream& operator >> (istream& is, Teacher& teacher);



};


#endif