#include "CommissionMember.h"
#include <iomanip>

CommissionMember& CommissionMember::operator=(const CommissionMember& other) {
    if (this != &other) {
        Human::operator=(other);
        this->commissionName = other.commissionName;
        this->biographyCount = other.biographyCount;
        for (int i = 0; i < this->biographyCount; i++) {
            this->biography[i] = other.biography[i];
        }
    }
    return *this;
}

String CommissionMember::getCommissionName() const {return commissionName;}

int CommissionMember::getBiographyCount() const {return biographyCount;}

String CommissionMember::getBiography(int index) const 
{
    if (index >= 0 && index < biographyCount) return biography[index];
    return String("");
}

void CommissionMember::setCommissionName(const String& commissionName) {this->commissionName = commissionName;}

bool CommissionMember::addBiography(const String& biographyLine) 
{
    if (biographyCount < MAX_BIOGRAPHY) 
    {
        biography[biographyCount] = biographyLine;
        biographyCount++;
        return true;
    }
    return false;
}

bool CommissionMember::setBiography(int index, const String& biographyLine) 
{
    if (index >= 0 && index < biographyCount) 
    {
        biography[index] = biographyLine;
        return true;
    }
    return false;
}

void CommissionMember::printHeader() const {
    cout << left << setw(15) << "Фамилия";
    cout << left << setw(15) << "Имя";
    cout << left << setw(12) << "Год рожд.";
    cout << left << setw(20) << "Название комиссии";
    cout << left << setw(30) << "Биография";
    cout << endl;
}

void CommissionMember::printInfo() const {
    cout << left << setw(15) << this->lastName;
    cout << left << setw(15) << this->firstName;
    cout << left << setw(12) << this->birthYear;
    cout << left << setw(20) << this->commissionName;

    String bioList = "";
    for (int i = 0; i < biographyCount; i++)
    {
        if (i > 0) bioList += ", ";
        bioList += biography[i];
    }
    cout << left << setw(30) << bioList;
    cout << endl;
}

char CommissionMember::editMenu() const {
    cout << " 1. Изменить фамилию   " << endl;
    cout << " 2. Изменить имя       " << endl;
    cout << " 3. Изменить год рожд. " << endl;
    cout << " 4. Изменить комиссию  " << endl;
    cout << " 5. Добавить биографию " << endl;
    cout << " 6. Показать биографию " << endl;
    cout << " 7. Изменить все       " << endl;
    cout << " 0. Назад              " << endl;

    char option;
    cout << "Выбор: ";
    cin >> option;
    return option;
}

void CommissionMember::editFields() {
    char choice;
    do {
        cout << "\nРЕДАКТИРОВАНИЕ COMMISSION MEMBER" << endl;
        cout << "Текущие данные:" << endl;
        this->printHeader();
        this->printInfo();
        cout << endl;

        choice = editMenu();

        switch (choice) {
        case '1': {
            String newLastName;
            cout << "Введите новую фамилию: ";
            cin.ignore(1000, '\n');
            cin >> newLastName;
            this->setLastName(newLastName);
            cout << "Фамилия обновлена!" << endl;
            break;
        }
        case '2': {
            String newFirstName;
            cout << "Введите новое имя: ";
            cin.ignore(1000, '\n');
            cin >> newFirstName;
            this->setFirstName(newFirstName);
            cout << "Имя обновлено!" << endl;
            break;
        }
        case '3': {
            int newBirthYear;
            cout << "Введите новый год рождения: ";
            cin >> newBirthYear;
            this->setBirthYear(newBirthYear);
            cout << "Год рождения обновлен!" << endl;
            break;
        }
        case '4': {
            String newCommission;
            cout << "Введите новое название комиссии: ";
            cin.ignore(1000, '\n');
            cin >> newCommission;
            this->setCommissionName(newCommission);
            cout << "Название комиссии обновлено!" << endl;
            break;
        }
        case '5': {
            String bio;
            cout << "Введите пункт биографии: ";
            cin.ignore(1000, '\n');
            cin >> bio;
            if (this->addBiography(bio)) {
                cout << "Биография добавлена!" << endl;
            }
            else {
                cout << "Не удалось добавить биографию!" << endl;
            }
            break;
        }
        case '6': {
            cout << "Биография (" << biographyCount << " пунктов):" << endl;
            for (int i = 0; i < biographyCount; i++) {
                cout << i + 1 << ". " << biography[i] << endl;
            }
            break;
        }
        case '7': {
            CommissionMember newMember;
            cin >> newMember;
            *this = newMember;
            cout << "Все данные обновлены!" << endl;
            break;
        }
        case '0':
            cout << "Выход из редактирования..." << endl;
            break;
        default:
            cout << "Неверный выбор!" << endl;
        }
    } while (choice != '0');
}

ostream& operator<<(ostream& os, const CommissionMember& member) {
    os << static_cast<const Human&>(member) << " " << member.commissionName;
    for (int i = 0; i < member.biographyCount; i++) {
        os << " " << member.biography[i];
    }
    return os;
}

istream& operator>>(istream& is, CommissionMember& member) {
    is >> static_cast<Human&>(member);
    cout << "Введите название комиссии: ";
    cin.ignore(1000, '\n');
    is >> member.commissionName;

    cout << "Введите кол-во пунктов биографии (не больше " << MAX_BIOGRAPHY << "): ";
    is >> member.biographyCount;
    if (member.biographyCount > MAX_BIOGRAPHY) {
        member.biographyCount = MAX_BIOGRAPHY;
    }

    for (int i = 0; i < member.biographyCount; i++) {
        cout << "Введите пункт биографии " << i + 1 << ": ";
        cin.ignore(1000, '\n');
        is >> member.biography[i];
    }

    return is;
}

