
#ifndef TEACHERCOMMISSIONMEMBER_H
#define TEACHERCOMMISSIONMEMBER_H
#define MAX_COMMISSION_WORKS 8

#include "Teacher.h"
#include "CommissionMember.h"

class TeacherCommissionMember : public Teacher, public CommissionMember
{
private:
    String commissionWorks[MAX_COMMISSION_WORKS];
    int worksCount = 0;
public:
    TeacherCommissionMember() {}
    TeacherCommissionMember(String firstName, String lastName, int birthYear, String position, String specialty, String commissionName) : Human(firstName, lastName, birthYear), Teacher(firstName, lastName, birthYear, position, specialty), CommissionMember(firstName, lastName, birthYear, commissionName), worksCount(0) {}
    virtual ~TeacherCommissionMember() {}
    TeacherCommissionMember& operator=(const TeacherCommissionMember& other);

    int getWorksCount() const;
    String getCommissionWork(int index) const;

    bool addCommissionWork(const String work);
    bool setCommissionWork(int index, const String work);

    virtual char editMenu() const override;
    virtual void editFields() override;

    virtual void printHeader() const override;
    virtual void printInfo() const override;

    friend ostream& operator << (ostream& os, const TeacherCommissionMember& tcm);
    friend istream& operator >> (istream& is, TeacherCommissionMember& tcm);
};


#endif