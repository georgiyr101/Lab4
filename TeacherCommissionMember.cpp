#include "TeacherCommissionMember.h"
#include "../Lab4/Input.h"
#include <iomanip>
#include <sstream>

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
    cout << left << setw(15) << "Last Name";
    cout << left << setw(15) << "First Name";
    cout << left << setw(12) << "Birth Year"; 
    cout << left << setw(20) << "Position";
    cout << left << setw(20) << "Specialty";
    cout << left << setw(15) << "Publications"; 
    cout << left << setw(20) << "Commission Name";
    cout << left << setw(20) << "Biography"; 
    cout << left << setw(30) << "Commission Works" << endl; 
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
    tcm.setCommissionName(inputString(is, "Enter commission name (Latin letters, space or hyphen): "));

    cout << "Enter number of biography lines (0-" << MAX_BIOGRAPHY << "): ";
    tcm.biographyCount = inputNumber(is, 0, MAX_BIOGRAPHY, "Enter number of biography lines (0-5): ");
    if (tcm.biographyCount > MAX_BIOGRAPHY) {
        tcm.biographyCount = MAX_BIOGRAPHY;
    }
    for (int i = 0; i < tcm.biographyCount; i++) {
        tcm.biography[i] = inputString(is, "������� ����� ��������� (������ ��������, ������ ��� �����): ");
    }
    tcm.worksCount = inputNumber<int>(is, 0, MAX_COMMISSION_WORKS, "Enter number of commission works (0-5): ");
    if (tcm.worksCount > MAX_COMMISSION_WORKS) {
        tcm.worksCount = MAX_COMMISSION_WORKS;
    }
    is.ignore(1000, '\n');
    for (int i = 0; i < tcm.worksCount; i++) {
        tcm.commissionWorks[i] = inputString(is, "Enter commission work title (Latin letters, space or hyphen): ");
    }

    return is;
}

char TeacherCommissionMember::editMenu() const {
    cout << " 1. Edit last name            " << endl;
    cout << " 2. Edit first name                " << endl;
    cout << " 3. Edit birth year          " << endl;
    cout << " 4. Edit position          " << endl;
    cout << " 5. Edit specialty      " << endl;
    cout << " 6. Add publication " << endl;
    cout << " 7. Edit commission name  " << endl;
    cout << " 8. Add biography          " << endl;
    cout << " 9. Add commission work " << endl;
    cout << " 10. Show publications        " << endl;
    cout << " 11. Show biography         " << endl;
    cout << " 12. Show commission works " << endl;
    cout << " 13. Change all        " << endl;
    cout << " 0. Exit                       " << endl;

    char option;
    cout << "Select option: ";
    cin >> option;
    return option;
}

void TeacherCommissionMember::editFields() {
    char choice;
    do {
        cout << "\nEDITING TEACHER COMMISSION MEMBER " << endl;
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
            publication = inputString(cin, "������� ������� ���������� (������ ��������, ������ ��� �����): ");
            if (this->addScientificPublication(publication)) {cout << "���������� ���������!" << endl;}
            else {cout << "�� ������� �������� ����������!" << endl;}
            break;
        }
        case '7': {
            string newCommission;
            cin.ignore(1000, '\n');
            newCommission = inputString(cin, "Enter commission name (Latin letters, space or hyphen): ");
            this->setCommissionName(newCommission);
            cout << "Commission name changed!" << endl;
            break;
        }
        case '8': {
            string bio;
            cin.ignore(1000, '\n');
            bio = inputString(cin, "Enter biography line (Latin letters, space or hyphen): ");
            if (this->addBiography(bio)) {cout << "Biography line added!" << endl;}
            else {cout << "Failed to add biography line!" << endl;}
            break;
        }
        case '9': {
            string work;
            cin.ignore(1000, '\n');
            work = inputString(cin, "Enter commission work title (Latin letters, space or hyphen): ");
            if (this->addCommissionWork(work)) {cout << "Commission work added!" << endl;}
            else {cout << "Failed to add commission work!" << endl;}
            break;
        }
        case '10': {
            cout << "Publications (" << publicationsCount << "):" << endl;
            for (int i = 0; i < publicationsCount; i++) {
                cout << i + 1 << ". " << scientificPublications[i] << endl;
            }
            break;
        }
        case '11': {
            cout << "Biography (" << biographyCount << " lines):" << endl;
            for (int i = 0; i < biographyCount; i++) {
                cout << i + 1 << ". " << biography[i] << endl;
            }
            break;
        }
        case '12': {
            cout << "������ � �������� (" << worksCount << "):" << endl;
            for (int i = 0; i < worksCount; i++) {
                cout << i + 1 << ". " << commissionWorks[i] << endl;
            }
            break;
        }
        case '13': {
            TeacherCommissionMember newTCM;
            cin >> newTCM;
            *this = newTCM;
            cout << "All fields changed!" << endl;
            break;
        }
        case '0':
            cout << "Exiting edit mode..." << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
        }
    while (choice != '0');
}

void TeacherCommissionMember::saveTextRecord(ostream& os) const {
    Teacher::saveTextRecord(os);
    os << ";" << commissionName << ";" << biographyCount;
    for (int i = 0; i < biographyCount; i++) {
        os << ";" << biography[i];
    }
    os << ";" << worksCount;
    for (int i = 0; i < worksCount; i++) {
        os << ";" << commissionWorks[i];
    }
}

void TeacherCommissionMember::saveBinaryRecord(ostream& os) const {
    Teacher::saveBinaryRecord(os);
    int len;

    len = static_cast<int>(commissionName.size());
    os.write(reinterpret_cast<const char*>(&len), sizeof(len));
    if (len > 0) os.write(commissionName.data(), len);

    os.write(reinterpret_cast<const char*>(&biographyCount), sizeof(biographyCount));
    for (int i = 0; i < biographyCount; i++) {
        len = static_cast<int>(biography[i].size());
        os.write(reinterpret_cast<const char*>(&len), sizeof(len));
        if (len > 0) os.write(biography[i].data(), len);
    }

    os.write(reinterpret_cast<const char*>(&worksCount), sizeof(worksCount));
    for (int i = 0; i < worksCount; i++) {
        len = static_cast<int>(commissionWorks[i].size());
        os.write(reinterpret_cast<const char*>(&len), sizeof(len));
        if (len > 0) os.write(commissionWorks[i].data(), len);
    }
}

void TeacherCommissionMember::loadFromText(istream& is) {
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
                            
                            // Parse CommissionMember data: commissionName;biographyCount;biography...
                            if (pos < line.length()) {
                                nextPos = line.find(';', pos);
                                if (nextPos != string::npos) {
                                    commissionName = line.substr(pos, nextPos - pos);
                                    pos = nextPos + 1;
                                    
                                    nextPos = line.find(';', pos);
                                    if (nextPos != string::npos) {
                                        countStr = line.substr(pos, nextPos - pos);
                                        istringstream bcss(countStr);
                                        bcss >> biographyCount;
                                        pos = nextPos + 1;
                                        
                                        for (int i = 0; i < biographyCount && i < MAX_BIOGRAPHY; i++) {
                                            nextPos = line.find(';', pos);
                                            if (nextPos != string::npos) {
                                                biography[i] = line.substr(pos, nextPos - pos);
                                                pos = nextPos + 1;
                                            } else {
                                                biography[i] = line.substr(pos);
                                                break;
                                            }
                                        }
                                        
                                        // Parse TeacherCommissionMember data: worksCount;commissionWorks...
                                        if (pos < line.length()) {
                                            nextPos = line.find(';', pos);
                                            if (nextPos != string::npos) {
                                                countStr = line.substr(pos, nextPos - pos);
                                                istringstream wss(countStr);
                                                wss >> worksCount;
                                                pos = nextPos + 1;
                                                
                                                for (int i = 0; i < worksCount && i < MAX_COMMISSION_WORKS; i++) {
                                                    nextPos = line.find(';', pos);
                                                    if (nextPos != string::npos) {
                                                        commissionWorks[i] = line.substr(pos, nextPos - pos);
                                                        pos = nextPos + 1;
                                                    } else {
                                                        commissionWorks[i] = line.substr(pos);
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
                }
            }
        }
    }
}

void TeacherCommissionMember::loadFromBinary(istream& is) {
    Teacher::loadFromBinary(is);
    int len;

    is.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (len > 0) {
        commissionName.resize(len);
        is.read(&commissionName[0], len);
    }

    is.read(reinterpret_cast<char*>(&biographyCount), sizeof(biographyCount));
    for (int i = 0; i < biographyCount && i < MAX_BIOGRAPHY; i++) {
        is.read(reinterpret_cast<char*>(&len), sizeof(len));
        if (len > 0) {
            biography[i].resize(len);
            is.read(&biography[i][0], len);
        }
    }

    is.read(reinterpret_cast<char*>(&worksCount), sizeof(worksCount));
    for (int i = 0; i < worksCount && i < MAX_COMMISSION_WORKS; i++) {
        is.read(reinterpret_cast<char*>(&len), sizeof(len));
        if (len > 0) {
            commissionWorks[i].resize(len);
            is.read(&commissionWorks[i][0], len);
        }
    }
}
