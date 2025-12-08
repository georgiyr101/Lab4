#include "TeacherCommissionMember.h"
#include "../Lab4/Input.h"
#include <iomanip>

TeacherCommissionMember& TeacherCommissionMember::operator=(const TeacherCommissionMember& other) {
    if (this != &other) {
        Human::operator=(other);
        Teacher::operator=(other);
        CommissionMember::operator=(other);
        this->worksCount = other.worksCount;
        for (int i = 0; i < this->worksCount; i++) {
            this->commissionWorks[i] = other.commissionWorks[i];
        }
    }
    return *this;
}

int TeacherCommissionMember::getWorksCount() const {
    return worksCount;
}

string TeacherCommissionMember::getCommissionWork(int index) const {
    if (index >= 0 && index < worksCount) {
        return commissionWorks[index];
    }
    return string("");
}

bool TeacherCommissionMember::addCommissionWork(const string work) {
    if (worksCount < MAX_COMMISSION_WORKS) {
        commissionWorks[worksCount] = work;
        worksCount++;
        return true;
    }
    return false;
}

bool TeacherCommissionMember::setCommissionWork(int index, const string work) {
    if (index >= 0 && index < worksCount) {
        commissionWorks[index] = work;
        return true;
    }
    return false;
}

void TeacherCommissionMember::printHeader() const {
    cout << left << setw(15) << "Фамилия";
    cout << left << setw(15) << "Имя";
    cout << left << setw(12) << "Год рожд."; 
    cout << left << setw(20) << "Должность";
    cout << left << setw(20) << "Специальность";
    cout << left << setw(15) << "Научные работы"; 
    cout << left << setw(20) << "Имя комиссии";
    cout << left << setw(20) << "Биография"; 
    cout << left << setw(30) << "Работы в комиссии" << endl; 
}

void TeacherCommissionMember::printInfo() const {
    cout << left << setw(15) << this->getLastName();
    cout << left << setw(15) << this->getFirstName();
    cout << left << setw(12) << this->getBirthYear(); 
    cout << left << setw(20) << this->Teacher::getPosition();
    cout << left << setw(20) << this->Teacher::getSpecialty();
    string publicationsList = "";
    for (int i = 0; i < publicationsCount; i++)
    {
        if (i > 0) publicationsList += ", ";
        publicationsList += scientificPublications[i];
    }
    cout << left << setw(15) << publicationsList;
    cout << left << setw(20) << this->CommissionMember::getCommissionName();
    string bioList = "";
    for (int i = 0; i < biographyCount; i++)
    {
        if (i > 0) bioList += ", ";
        bioList += biography[i];
    }
    cout << left << setw(20) << bioList;

    string worksList = "";
    for (int i = 0; i < worksCount; i++) {
        if (i > 0) worksList += ", ";
        worksList += commissionWorks[i];
    }
    cout << left << setw(30) << worksList;
    cout << endl;
}

ostream& operator<<(ostream& os, const TeacherCommissionMember& tcm) {
    os << static_cast<const Teacher&>(tcm);

    for (int i = 0; i < tcm.CommissionMember::getBiographyCount(); i++) {
        os << " " << tcm.CommissionMember::getBiography(i);
    }

    for (int i = 0; i < tcm.worksCount; i++) {
        os << " " << tcm.commissionWorks[i];
    }

    return os;
}

istream& operator>>(istream& is, TeacherCommissionMember& tcm) 
{
    is >> static_cast<Teacher&>(tcm);
    cout << "Введите название комиссии (только латиница, пробел или дефис): ";
    tcm.setCommissionName(inputString());

    cout << "Введите кол-во пунктов биографии (0-" << MAX_BIOGRAPHY << "): ";
    tcm.biographyCount = inputNumber(is, 0, MAX_BIOGRAPHY);
    if (tcm.biographyCount > MAX_BIOGRAPHY) {
        tcm.biographyCount = MAX_BIOGRAPHY;
    }
    for (int i = 0; i < tcm.biographyCount; i++) {
        cout << "Введите пункт биографии " << i + 1 << "(только латиница, пробел или дефис): ";
        tcm.biography[i] = inputString();
    }
    cout << "Введите кол-во работ в комиссии (0-" << MAX_COMMISSION_WORKS << "): ";
    tcm.worksCount = inputNumber(is, 0, MAX_COMMISSION_WORKS);
    if (tcm.worksCount > MAX_COMMISSION_WORKS) {
        tcm.worksCount = MAX_COMMISSION_WORKS;
    }
    is.ignore(1000, '\n');
    for (int i = 0; i < tcm.worksCount; i++) {
        cout << "Введите название работы в комиссии " << i + 1 << "(только латиница, пробел или дефис): ";
        tcm.commissionWorks[i] = inputString();
    }

    return is;
}

char TeacherCommissionMember::editMenu() const {
    cout << " 1. Изменить фамилию            " << endl;
    cout << " 2. Изменить имя                " << endl;
    cout << " 3. Изменить год рожд.          " << endl;
    cout << " 4. Изменить должность          " << endl;
    cout << " 5. Изменить специальность      " << endl;
    cout << " 6. Добавить научную публикацию " << endl;
    cout << " 7. Изменить название комиссии  " << endl;
    cout << " 8. Добавить биографию          " << endl;
    cout << " 9. Добавить работу в комиссии " << endl;
    cout << " 10. Показать публикации        " << endl;
    cout << " 11. Показать биографию         " << endl;
    cout << " 12. Показать работы в комиссии " << endl;
    cout << " 13. Изменить все данные        " << endl;
    cout << " 0. Назад                       " << endl;

    char option;
    cout << "Выбор: ";
    cin >> option;
    return option;
}

void TeacherCommissionMember::editFields() {
    char choice;
    do {
        cout << "\nРЕДАКТИРОВАНИЕ TEACHER COMMISSION MEMBER " << endl;
        cout << "Текущие данные:" << endl;
        this->printHeader();
        this->printInfo();
        cout << endl;

        choice = editMenu();

        switch (choice) {
        case '1': {
            string newLastName;
            cout << "Введите новую фамилию: ";
            cin.ignore(1000, '\n');
            cin >> newLastName;
            this->setLastName(newLastName);
            cout << "Фамилия обновлена!" << endl;
            break;
        }
        case '2': {
            string newFirstName;
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
            string newPosition;
            cout << "Введите новую должность: ";
            cin.ignore(1000, '\n');
            cin >> newPosition;
            this->setPosition(newPosition);
            cout << "Должность обновлена!" << endl;
            break;
        }
        case '5': {
            string newSpecialty;
            cout << "Введите новую специальность: ";
            cin.ignore(1000, '\n');
            cin >> newSpecialty;
            this->setSpecialty(newSpecialty);
            cout << "Специальность обновлена!" << endl;
            break;
        }
        case '6': {
            string publication;
            cout << "Введите научную публикацию: ";
            cin.ignore(1000, '\n');
            cin >> publication;
            if (this->addScientificPublication(publication)) {
                cout << "Публикация добавлена!" << endl;
            }
            else {
                cout << "Не удалось добавить публикацию!" << endl;
            }
            break;
        }
        case '7': {
            string newCommission;
            cout << "Введите новое название комиссии: ";
            cin.ignore(1000, '\n');
            cin >> newCommission;
            this->setCommissionName(newCommission);
            cout << "Название комиссии обновлено!" << endl;
            break;
        }
        case '8': {
            string bio;
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
        case '9': {
            string work;
            cout << "Введите работу в комиссии: ";
            cin.ignore(1000, '\n');
            cin >> work;
            if (this->addCommissionWork(work)) {
                cout << "Работа в комиссии добавлена!" << endl;
            }
            else {
                cout << "Не удалось добавить работу!" << endl;
            }
            break;
        }
        case '10': {
            cout << "Научные публикации (" << publicationsCount << "):" << endl;
            for (int i = 0; i < publicationsCount; i++) {
                cout << i + 1 << ". " << scientificPublications[i] << endl;
            }
            break;
        }
        case '11': {
            cout << "Биография (" << biographyCount << " пунктов):" << endl;
            for (int i = 0; i < biographyCount; i++) {
                cout << i + 1 << ". " << biography[i] << endl;
            }
            break;
        }
        case '12': {
            cout << "Работы в комиссии (" << worksCount << "):" << endl;
            for (int i = 0; i < worksCount; i++) {
                cout << i + 1 << ". " << commissionWorks[i] << endl;
            }
            break;
        }
        case '13': {
            TeacherCommissionMember newTCM;
            cin >> newTCM;
            *this = newTCM;
            cout << "Все данные обновлены!" << endl;
            break;
        }
        case '0':
            cout << "Выход из редактирования..." << endl;
            break;
        default:
            cout << "Неверный выбор!" << endl;
        }
        }
    while (choice != '0');
}
