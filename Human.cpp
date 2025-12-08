#include "Human.h"
#include <iomanip>
#include "../Lab4/Input.h"

Human& Human::operator=(const Human& other) {
    if (this != &other) {
        this->firstName = other.firstName;
        this->lastName = other.lastName;
        this->birthYear = other.birthYear;
    }
    return *this;
}


string Human::getFirstName() const { return this->firstName; }
string Human::getLastName() const { return this->lastName; }
int Human::getBirthYear() const { return this->birthYear; }

void Human::setFirstName(const string& first) { this->firstName = first; }
void Human::setLastName(const string& last) { this->lastName = last; }
void Human::setBirthYear(int year) { this->birthYear = year; }

ostream& operator<<(ostream& os, const Human& h) {
    os << h.lastName << " " << h.firstName << " " << h.birthYear;
    return os;
}

istream& operator>>(istream& is, Human& h) {
    std::cout << "Введите фамилию (только латиница, пробел или дефис): ";
    h.setLastName(inputString());
    std::cout << "Введите имя (только латиница, пробел или дефис): ";
    h.setFirstName(inputString());
    std::cout << "Введите год рождения: ";
    h.setBirthYear(inputNumber<int>(is, 1900, 2025));
    return is;
}



