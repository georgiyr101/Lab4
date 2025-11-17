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
SearchParams Human::currentSearchParams = LAST_NAME;

bool Human::operator==(const Human& other) const {
    if (currentSearchParams == LAST_NAME) {return lastName == other.lastName;}
    else if (currentSearchParams == FIRST_NAME) {return firstName == other.firstName;}
    else if (currentSearchParams == BIRTH_YEAR) {return birthYear == other.birthYear;}
    else if (currentSearchParams == ALL_PARAMS) {return ((lastName == other.lastName) && (firstName == other.firstName) && (birthYear == other.birthYear));}
    return false;
}
bool Human::operator<(const Human& other) const {
    if (currentSearchParams == LAST_NAME) {
        return this->lastName < other.lastName;
    }
    else if (currentSearchParams == FIRST_NAME) {
        return this->firstName < other.firstName;
    }
    else if (currentSearchParams == BIRTH_YEAR) {
        return this->birthYear < other.birthYear;
    }
    return true;
}

String Human::getFirstName() const { return this->firstName; }
String Human::getLastName() const { return this->lastName; }
int Human::getBirthYear() const { return this->birthYear; }

void Human::setFirstName(const String& first) { this->firstName = first; }
void Human::setLastName(const String& last) { this->lastName = last; }
void Human::setBirthYear(int year) { this->birthYear = year; }
void Human::setSearchParams(SearchParams params) { currentSearchParams = params; }

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



