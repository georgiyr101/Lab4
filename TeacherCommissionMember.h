
#ifndef TEACHERCOMMISSIONMEMBER_H
#define TEACHERCOMMISSIONMEMBER_H
#define MAX_COMMISSION_WORKS 8

#include "Teacher.h"
#include "CommissionMember.h"

class TeacherCommissionMember : public Teacher, public CommissionMember
{
private:
    string commissionWorks[MAX_COMMISSION_WORKS];
    int worksCount = 0;
public:
    TeacherCommissionMember() {}
    TeacherCommissionMember(string firstName, string lastName, int birthYear, string position, string specialty, string commissionName) : Human(firstName, lastName, birthYear), Teacher(firstName, lastName, birthYear, position, specialty), CommissionMember(firstName, lastName, birthYear, commissionName), worksCount(0) {}
    virtual ~TeacherCommissionMember() {}
    TeacherCommissionMember& operator=(const TeacherCommissionMember& other);

    int getWorksCount() const;
    string getCommissionWork(int index) const;

    bool addCommissionWork(const string work);
    bool setCommissionWork(int index, const string work);

    virtual char editMenu() const override;
    virtual void editFields() override;

    virtual void printHeader() const override;
    virtual void printInfo() const override;

    virtual void saveTextRecord(ostream& os) const override;
    virtual void saveBinaryRecord(ostream& os) const override;

    virtual void loadFromText(istream& is) override;
    virtual void loadFromBinary(istream& is) override;

    friend ostream& operator << (ostream& os, const TeacherCommissionMember& tcm);
    friend istream& operator >> (istream& is, TeacherCommissionMember& tcm);
};


#endif