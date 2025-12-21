#include "Human.h"
#include <iomanip>
#include <string>
#include <sstream>
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

istream& operator>>(istream& is, Human& h) 
{
    h.setLastName(inputName(is, "¬ведите фамилию (только латиница, пробел и дефис): "));
    h.setFirstName(inputName(is, "¬ведите им€ (только латиница, пробел и дефис): "));
    h.setBirthYear(inputNumber<int>(is, 1900, 2025, "¬ведите год рождени€: "));
    return is;
}

void Human::saveTextRecord(ostream& os) const {
    string birthYearStr = to_string(this->birthYear);
    os << this->firstName << ";" << this->lastName << ";" << birthYearStr;
}

void Human::saveBinaryRecord(ostream& os) const {
    int len;

    len = static_cast<int>(firstName.size());
    os.write(reinterpret_cast<const char*>(&len), sizeof(len));
    if (len > 0) os.write(firstName.data(), len);

    len = static_cast<int>(lastName.size());
    os.write(reinterpret_cast<const char*>(&len), sizeof(len));
    if (len > 0) os.write(lastName.data(), len);

    string birthYearStr = to_string(this->birthYear);
    len = static_cast<int>(birthYearStr.size());
    os.write(reinterpret_cast<const char*>(&len), sizeof(len));
    if (len > 0) os.write(birthYearStr.data(), len);
}

void Human::loadFromText(istream& is) {
    string line;
    getline(is, line);

    // Parse line: firstName;lastName;birthYear
    size_t pos = 0;
    size_t nextPos = line.find(';', pos);
    if (nextPos != string::npos) {
        firstName = line.substr(pos, nextPos - pos);
        pos = nextPos + 1;

        nextPos = line.find(';', pos);
        if (nextPos != string::npos) {
            lastName = line.substr(pos, nextPos - pos);
            pos = nextPos + 1;

            string birthYearStr = line.substr(pos);
            istringstream bys(birthYearStr);
            bys >> birthYear;
        }
    }
}

void Human::loadFromBinary(istream& is) {
    int len;

    is.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (len > 0) {
        firstName.resize(len);
        is.read(&firstName[0], len);
    }

    is.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (len > 0) {
        lastName.resize(len);
        is.read(&lastName[0], len);
    }

    is.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (len > 0) {
        string birthYearStr;
        birthYearStr.resize(len);
        is.read(&birthYearStr[0], len);
        istringstream bys(birthYearStr);
        bys >> birthYear;
    }
}



