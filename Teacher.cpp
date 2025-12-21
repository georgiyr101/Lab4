#include "Teacher.h"
#include "../Lab4/Input.h"
#include <iostream>
#include <iomanip>
#include <sstream>

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

string Teacher::getPosition() const { return position; }

string Teacher::getSpecialty() const { return specialty; }

int Teacher::getPublicationsCount() const {return publicationsCount;}

string Teacher::getScientificPublication(int index) const 
{
    if (index >= 0 && index < publicationsCount) { return scientificPublications[index]; }
    return string("");
}

void Teacher::setPosition(const string& position) {this->position = position;}

void Teacher::setSpecialty(const string& specialty) {this->specialty = specialty;}

bool Teacher::addScientificPublication(const string& publication) 
{
    if (publicationsCount < MAX_PUBLICATIONS) 
    {
        scientificPublications[publicationsCount] = publication;
        publicationsCount++;
        return true;
    }
    return false;
}

bool Teacher::setScientificPublication(int index, const string& publication) 
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
    teacher.setPosition(inputString(is, "Enter position (Latin letters, space or hyphen): "));
    teacher.setSpecialty(inputString(is, "Enter specialty (Latin letters, space or hyphen): "));
    teacher.publicationsCount = inputNumber<int>(is, 1, MAX_PUBLICATIONS, "Enter number of publications (max 10): ");
    if (teacher.publicationsCount > MAX_PUBLICATIONS) 
    {
        teacher.publicationsCount = MAX_PUBLICATIONS;
    }

    for (int i = 0; i < teacher.publicationsCount; i++) 
    {
        teacher.scientificPublications[i] = inputString(is, "Enter publication title (Latin letters, space or hyphen): ");
    }
    return is;
}

void Teacher::printHeader() const {
    cout << left << setw(15) << "Last Name";
    cout << left << setw(15) << "First Name";
    cout << left << setw(12) << "Birth Year";
    cout << left << setw(20) << "Position";
    cout << left << setw(20) << "Specialty";
    cout << left << setw(30) << "Publications"; 
    cout << endl;
}

void Teacher::printInfo() const {
    cout << left << setw(15) << this->lastName;
    cout << left << setw(15) << this->firstName;
    cout << left << setw(12) << this->birthYear;
    cout << left << setw(20) << this->position;
    cout << left << setw(20) << this->specialty;

    string publicationsList = "";
    for (int i = 0; i < publicationsCount; i++)
    {
        if (i > 0) publicationsList += ", ";
        publicationsList += scientificPublications[i];
    }
    cout << left << setw(30) << publicationsList; 
    cout << endl;
}

char Teacher::editMenu() const {
    cout << " 1. Edit last name   " << endl;
    cout << " 2. Edit first name       " << endl;
    cout << " 3. Edit birth year " << endl;
    cout << " 4. Edit position " << endl;
    cout << " 5. Edit specialty " << endl;
    cout << " 6. Add publication " << endl;
    cout << " 7. Show publications " << endl;
    cout << " 8. Change all " << endl;
    cout << " 0. Exit              " << endl;

    char option;
    cout << "Select option: ";
    cin >> option;
    return option;
}

void Teacher::editFields() {
    char choice;
    do {
        cout << "\nEDITING TEACHER" << endl;
        cout << "Current data:" << endl;
        this->printHeader();
        this->printInfo();
        cout << endl;

        choice = editMenu();

        switch (choice) {
        case '1': {
            string newLastName;
            cin.ignore(1000, '\n');
            newLastName = inputName(cin, "Enter last name (Latin letters, space or hyphen): ");
            this->setLastName(newLastName);
            cout << "Last name changed!" << endl;
            break;
        }
        case '2': {
            string newFirstName;
            cin.ignore(1000, '\n');
            newFirstName = inputName(cin, "Enter first name (Latin letters, space or hyphen): ");
            this->setFirstName(newFirstName);
            cout << "First name changed!" << endl;
            break;
        }
        case '3': {
            int newBirthYear;
            newBirthYear = inputNumber<int>(cin, 1925, 2007, "Enter birth year: ");
            this->setBirthYear(newBirthYear);
            cout << "Birth year changed!" << endl;
            break;
        }
        case '4': {
            string newPosition;
            cin.ignore(1000, '\n');
            newPosition = inputString(cin, "Enter position (Latin letters, space or hyphen): ");
            this->setPosition(newPosition);
            cout << "Position changed!" << endl;
            break;
        }
        case '5': {
            string newSpecialty;
            cin.ignore(1000, '\n');
            newSpecialty = inputString(cin, "Enter specialty (Latin letters, space or hyphen): ");
            this->setSpecialty(newSpecialty);
            cout << "Specialty changed!" << endl;
            break;
        }
        case '6': {
            string publication;
            cin.ignore(1000, '\n');
            publication = inputString(cin, "Enter publication title (Latin letters, space or hyphen): ");
            if (this->addScientificPublication(publication)) {
                cout << "Publication added!" << endl;
            }
            else {
                cout << "Failed to add publication!" << endl;
            }
            break;
        }
        case '7': {
            cout << "Publications (" << publicationsCount << "):" << endl;
            for (int i = 0; i < publicationsCount; i++) {
                cout << i + 1 << ". " << scientificPublications[i] << endl;
            }
            break;
        }
        case '8': {
            Teacher newTeacher;
            cin >> newTeacher;
            *this = newTeacher;
            cout << "All fields changed!" << endl;
            break;
        }
        case '0':
            cout << "Exiting edit mode..." << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
        }

    } while (choice != '0');
}

void Teacher::saveTextRecord(ostream& os) const {
    Human::saveTextRecord(os);
    os << ";" << position << ";" << specialty << ";" << publicationsCount;
    for (int i = 0; i < publicationsCount; i++) {
        os << ";" << scientificPublications[i];
    }
}

void Teacher::saveBinaryRecord(ostream& os) const {
    Human::saveBinaryRecord(os);
    int len;

    len = static_cast<int>(position.size());
    os.write(reinterpret_cast<const char*>(&len), sizeof(len));
    if (len > 0) os.write(position.data(), len);

    len = static_cast<int>(specialty.size());
    os.write(reinterpret_cast<const char*>(&len), sizeof(len));
    if (len > 0) os.write(specialty.data(), len);

    os.write(reinterpret_cast<const char*>(&publicationsCount), sizeof(publicationsCount));
    for (int i = 0; i < publicationsCount; i++) {
        len = static_cast<int>(scientificPublications[i].size());
        os.write(reinterpret_cast<const char*>(&len), sizeof(len));
        if (len > 0) os.write(scientificPublications[i].data(), len);
    }
}

void Teacher::loadFromText(istream& is) {
    string line;
    getline(is, line);
    
    // Parse Human data: firstName;lastName;birthYear
    size_t pos = 0;
    size_t nextPos = line.find(';', pos);
    if (nextPos != string::npos) {
        firstName = line.substr(pos, nextPos - pos);
        pos = nextPos + 1;
        
        nextPos = line.find(';', pos);
        if (nextPos != string::npos) {
            lastName = line.substr(pos, nextPos - pos);
            pos = nextPos + 1;
            
            nextPos = line.find(';', pos);
            if (nextPos != string::npos) {
                string birthYearStr = line.substr(pos, nextPos - pos);
                istringstream bys(birthYearStr);
                bys >> birthYear;
                pos = nextPos + 1;
                
                // Parse Teacher data: position;specialty;publicationsCount;publications...
                nextPos = line.find(';', pos);
                if (nextPos != string::npos) {
                    position = line.substr(pos, nextPos - pos);
                    pos = nextPos + 1;
                    
                    nextPos = line.find(';', pos);
                    if (nextPos != string::npos) {
                        specialty = line.substr(pos, nextPos - pos);
                        pos = nextPos + 1;
                        
                        nextPos = line.find(';', pos);
                        if (nextPos != string::npos) {
                            string countStr = line.substr(pos, nextPos - pos);
                            istringstream css(countStr);
                            css >> publicationsCount;
                            pos = nextPos + 1;
                            
                            for (int i = 0; i < publicationsCount && i < MAX_PUBLICATIONS; i++) {
                                nextPos = line.find(';', pos);
                                if (nextPos != string::npos) {
                                    scientificPublications[i] = line.substr(pos, nextPos - pos);
                                    pos = nextPos + 1;
                                } else {
                                    scientificPublications[i] = line.substr(pos);
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void Teacher::loadFromBinary(istream& is) {
    Human::loadFromBinary(is);
    int len;

    is.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (len > 0) {
        position.resize(len);
        is.read(&position[0], len);
    }

    is.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (len > 0) {
        specialty.resize(len);
        is.read(&specialty[0], len);
    }

    is.read(reinterpret_cast<char*>(&publicationsCount), sizeof(publicationsCount));
    for (int i = 0; i < publicationsCount && i < MAX_PUBLICATIONS; i++) {
        is.read(reinterpret_cast<char*>(&len), sizeof(len));
        if (len > 0) {
            scientificPublications[i].resize(len);
            is.read(&scientificPublications[i][0], len);
        }
    }
}



