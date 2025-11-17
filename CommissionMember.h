#ifndef COMMISSIONMEMBER_H
#define COMMISSIONMEMBER_H

#include "Human.h"

#define MAX_BIOGRAPHY 5

class CommissionMember : virtual public Human
{
protected:
	String commissionName = "";
	String biography[MAX_BIOGRAPHY];
	int biographyCount = 0;
public:
	CommissionMember(){}
	CommissionMember(String firstName, String lastName, int birthYear, String commissionName): Human(firstName, lastName, birthYear), commissionName(commissionName), biographyCount(0) {}
	virtual ~CommissionMember() {}
	CommissionMember& operator=(const CommissionMember& other);

	String getCommissionName() const;
	int getBiographyCount() const;
	String getBiography(int index) const;

	void setCommissionName(const String& commissionName);
	bool addBiography(const String& biographyLine);
	bool setBiography(int index, const String& biographyLine);

	virtual char editMenu() const override;
	virtual void editFields() override;

	virtual void printHeader() const override;
	virtual void printInfo() const override;

	friend ostream& operator << (ostream& os, const CommissionMember& member);
	friend istream& operator >> (istream& is, CommissionMember& member);

};


#endif