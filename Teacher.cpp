#include "Teacher.h"
#include <iostream>
#include <iomanip>

Teacher& Teacher::operator=(const Teacher& other) {
    if (this != &other) {
        Human::operator=(other);
        this->position = other.position;
        this->specialty = other.specialty;
        this->publicationsCount = other.publicationsCount;
        for (int i = 0; i < this->publicationsCount; i++) {
            this->scientificPublications[i] = other.scientificPublications[i];
        }
    }
    return *this;
}

String Teacher::getPosition() const { return position; }

String Teacher::getSpecialty() const { return specialty; }

int Teacher::getPublicationsCount() const {return publicationsCount;}

String Teacher::getScientificPublication(int index) const 
{
    if (index >= 0 && index < publicationsCount) 
    {
        return scientificPublications[index];
    }
    return String("");
}

void Teacher::setPosition(const String& position) {this->position = position;}

void Teacher::setSpecialty(const String& specialty) {this->specialty = specialty;}

bool Teacher::addScientificPublication(const String& publication) 
{
    if (publicationsCount < MAX_PUBLICATIONS) 
    {
        scientificPublications[publicationsCount] = publication;
        publicationsCount++;
        return true;
    }
    return false;
}

bool Teacher::setScientificPublication(int index, const String& publication) 
{
    if (index >= 0 && index < publicationsCount) 
    {
        scientificPublications[index] = publication;
        return true;
    }
    return false;
}

ostream& operator<<(ostream& os, const Teacher& teacher) {
    os << static_cast<const Human&>(teacher) << " " << teacher.position << " " << teacher.specialty;
    for (int i = 0; i < teacher.publicationsCount; i++) {
        os << " " << teacher.scientificPublications[i];
    }
    return os;
}

istream& operator>>(istream& is, Teacher& teacher) {
    is >> static_cast<Human&>(teacher);
    cout << "Введите должность: ";
    is.ignore(1000, '\n');
    is >> teacher.position;
    cout << "Введите специальность: ";
    is >> teacher.specialty;

    cout << "Введите количество научных трудов (не больше " << MAX_PUBLICATIONS << "): ";
    is >> teacher.publicationsCount;
    if (teacher.publicationsCount > MAX_PUBLICATIONS) 
    {
        teacher.publicationsCount = MAX_PUBLICATIONS;
    }

    for (int i = 0; i < teacher.publicationsCount; i++) 
    {
        cout << "Введите научную работу " << i + 1 << ": ";
        is.ignore(1000, '\n');
        is >> teacher.scientificPublications[i];
    }
    return is;
}

void Teacher::printHeader() const {
    cout << left << setw(15) << "Фамилия";
    cout << left << setw(15) << "Имя";
    cout << left << setw(12) << "Год рожд.";
    cout << left << setw(20) << "Должность";
    cout << left << setw(20) << "Специальность";
    cout << left << setw(30) << "Научные работы"; 
    cout << endl;
}

void Teacher::printInfo() const {
    cout << left << setw(15) << this->lastName;
    cout << left << setw(15) << this->firstName;
    cout << left << setw(12) << this->birthYear;
    cout << left << setw(20) << this->position;
    cout << left << setw(20) << this->specialty;

    String publicationsList = "";
    for (int i = 0; i < publicationsCount; i++)
    {
        if (i > 0) publicationsList += ", ";
        publicationsList += scientificPublications[i];
    }
    cout << left << setw(30) << publicationsList; 
    cout << endl;
}

char Teacher::editMenu() const {
    cout << " 1. Изменить фамилию   " << endl;
    cout << " 2. Изменить имя       " << endl;
    cout << " 3. Изменить год рожд. " << endl;
    cout << " 4. Изменить должность " << endl;
    cout << " 5. Изменить спец-сть  " << endl;
    cout << " 6. Добавить публикацию" << endl;
    cout << " 7. Показать публикации" << endl;
    cout << " 8. Изменить все       " << endl;
    cout << " 0. Назад              " << endl;

    char option;
    cout << "Выбор: ";
    cin >> option;
    return option;
}

void Teacher::editFields() {
    char choice;
    do {
        cout << "\nРЕДАКТИРОВАНИЕ TEACHER" << endl;
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
            String newPosition;
            cout << "Введите новую должность: ";
            cin.ignore(1000, '\n');
            cin >> newPosition;
            this->setPosition(newPosition);
            cout << "Должность обновлена!" << endl;
            break;
        }
        case '5': {
            String newSpecialty;
            cout << "Введите новую специальность: ";
            cin.ignore(1000, '\n');
            cin >> newSpecialty;
            this->setSpecialty(newSpecialty);
            cout << "Специальность обновлена!" << endl;
            break;
        }
        case '6': {
            String publication;
            cout << "Введите публикацию: ";
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
            cout << "Научные публикации (" << publicationsCount << "):" << endl;
            for (int i = 0; i < publicationsCount; i++) {
                cout << i + 1 << ". " << scientificPublications[i] << endl;
            }
            break;
        }
        case '8': {
            Teacher newTeacher;
            cin >> newTeacher;
            *this = newTeacher;
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



