#include "Human.h"
#include "Teacher.h"
#include "CommissionMember.h"
#include "TeacherCommissionMember.h"
#include "Menu.h"
#include <iostream>
#include <iomanip>
#include <locale.h>

int main()
{
	cout << "1. Работа с Teacher\n";
	cout << "2. Работа с CommissionMember\n";
	cout << "3. Работа с TeacherCommissionMember\n";
	cout << "0. Выход";

	int choice;
	cout << "Ваш выбор: ";
	cin >> choice;

	switch (choice)
	{
	case 1:
		teacherMenu();
		break;
	case 2:
		CommissionMemberMenu();
		break;
	case 3:
		TeacherCommissionMemberMenu();
		break;
	case 0:
		break();
	}

	return 0;
}