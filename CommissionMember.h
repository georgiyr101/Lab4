#ifndef COMMISSIONMEMBER_H
#define COMMISSIONMEMBER_H

#include "Human.h"

#define MAX_BIOGRAPHY 5

class CommissionMember : virtual public Human
{
protected:
	string commissionName = "";
	string biography[MAX_BIOGRAPHY];
	int biographyCount = 0;
public:
	CommissionMember(){}
	CommissionMember(string firstName, string lastName, int birthYear, string commissionName): Human(firstName, lastName, birthYear), commissionName(commissionName), biographyCount(0) {}
	virtual ~CommissionMember() {}
	CommissionMember& operator=(const CommissionMember& other);

	string getCommissionName() const;
	int getBiographyCount() const;
	string getBiography(int index) const;

	void setCommissionName(const string& commissionName);
	bool addBiography(const string& biographyLine);
	bool setBiography(int index, const string& biographyLine);

	virtual char editMenu() const override;
	virtual void editFields() override;

	virtual void printHeader() const override;
	virtual void printInfo() const override;

	friend ostream& operator << (ostream& os, const CommissionMember& member);
	friend istream& operator >> (istream& is, CommissionMember& member);

};


#endif
