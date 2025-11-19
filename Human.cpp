#include "Human.h"
#include <iomanip>

Human& Human::operator=(const Human& other) {
    if (this != &other) {
        this->firstName = other.firstName;
        this->lastName = other.lastName;
        this->birthYear = other.birthYear;
    }
    return *this;
}


String Human::getFirstName() const { return this->firstName; }
String Human::getLastName() const { return this->lastName; }
int Human::getBirthYear() const { return this->birthYear; }

void Human::setFirstName(const String& first) { this->firstName = first; }
void Human::setLastName(const String& last) { this->lastName = last; }
void Human::setBirthYear(int year) { this->birthYear = year; }

ostream& operator<<(ostream& os, const Human& h) {
    os << h.lastName << " " << h.firstName << " " << h.birthYear;
    return os;
}

istream& operator>>(istream& is, Human& h) {
    std::cout << "¬ведите фамилию: ";
    is.ignore(1000, '\n');
    is >> h.lastName;
    std::cout << "¬ведите им€: ";
    is >> h.firstName;
    std::cout << "¬ведите год рождени€: ";
    is >> h.birthYear;
    return is;
}



