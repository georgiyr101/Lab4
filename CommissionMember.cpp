#include "CommissionMember.h"
#include "../Lab4/Input.h"
#include <iomanip>
#include <sstream>

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

string CommissionMember::getCommissionName() const {return commissionName;}

int CommissionMember::getBiographyCount() const {return biographyCount;}

string CommissionMember::getBiography(int index) const 
{
    if (index >= 0 && index < biographyCount) return biography[index];
    return string("");
}

void CommissionMember::setCommissionName(const string& commissionName) {this->commissionName = commissionName;}

bool CommissionMember::addBiography(const string& biographyLine) 
{
    if (biographyCount < MAX_BIOGRAPHY) 
    {
        biography[biographyCount] = biographyLine;
        biographyCount++;
        return true;
    }
    return false;
}

bool CommissionMember::setBiography(int index, const string& biographyLine) 
{
    if (index >= 0 && index < biographyCount) 
    {
        biography[index] = biographyLine;
        return true;
    }
    return false;
}

void CommissionMember::printHeader() const {
    cout << left << setw(15) << "Last Name";
    cout << left << setw(15) << "First Name";
    cout << left << setw(12) << "Birth Year";
    cout << left << setw(20) << "Commission Name";
    cout << left << setw(30) << "Biography";
    cout << endl;
}

void CommissionMember::printInfo() const {
    cout << left << setw(15) << this->lastName;
    cout << left << setw(15) << this->firstName;
    cout << left << setw(12) << this->birthYear;
    cout << left << setw(20) << this->commissionName;

    string bioList = "";
    for (int i = 0; i < biographyCount; i++)
    {
        if (i > 0) bioList += ", ";
        bioList += biography[i];
    }
    cout << left << setw(30) << bioList;
    cout << endl;
}

char CommissionMember::editMenu() const {
    cout << " 1. �������� �������   " << endl;
    cout << " 2. �������� ���       " << endl;
    cout << " 3. �������� ��� ����. " << endl;
    cout << " 4. �������� ��������  " << endl;
    cout << " 5. �������� ��������� " << endl;
    cout << " 6. �������� ��������� " << endl;
    cout << " 7. �������� ���       " << endl;
    cout << " 0. �����              " << endl;

    char option;
    cout << "Select option: ";
    cin >> option;
    return option;
}

void CommissionMember::editFields() {
    char choice;
    do {
        cout << "\n�������������� COMMISSION MEMBER" << endl;
        cout << "������� ������:" << endl;
        this->printHeader();
        this->printInfo();
        cout << endl;

        choice = editMenu();

        switch (choice) {
        case '1': {
            string newLastName;
            cin.ignore(1000, '\n');
            newLastName = inputName(cin, "Enter last name: ");
            this->setLastName(newLastName);
            cout << "Last name changed!" << endl;
            break;
        }
        case '2': {
            string newFirstName;
            cin.ignore(1000, '\n');
            newFirstName = inputName(cin, "Enter first name: ");
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
            string newCommission;
            cin.ignore(1000, '\n');
            newCommission = inputString(cin, "Enter commission name (Latin letters, space or hyphen): ");
            this->setCommissionName(newCommission);
            cout << "Commission name changed!" << endl;
            break;
        }
        case '5': {
            string bio;
            cin.ignore(1000, '\n');
            bio = inputString(cin, "Enter biography line (Latin letters, space or hyphen): ");
            if (this->addBiography(bio)) {
                cout << "Biography line added!" << endl;
            }
            else {
                cout << "Failed to add biography line!" << endl;
            }
            break;
        }
        case '6': {
            cout << "Biography (" << biographyCount << " lines):" << endl;
            for (int i = 0; i < biographyCount; i++) {
                cout << i + 1 << ". " << biography[i] << endl;
            }
            break;
        }
        case '7': {
            CommissionMember newMember;
            cin >> newMember;
            *this = newMember;
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

ostream& operator<<(ostream& os, const CommissionMember& member) {
    os << static_cast<const Human&>(member) << " " << member.commissionName;
    for (int i = 0; i < member.biographyCount; i++) {
        os << " " << member.biography[i];
    }
    return os;
}

istream& operator>>(istream& is, CommissionMember& member) {
    is >> static_cast<Human&>(member);
    member.setCommissionName(inputString(is, "Enter commission name (Latin letters, space or hyphen): "));
    member.biographyCount = inputNumber<int>(is, 1, MAX_BIOGRAPHY, "Enter number of biography lines (max 5): ");
    if (member.biographyCount > MAX_BIOGRAPHY) { member.biographyCount = MAX_BIOGRAPHY;}
    for (int i = 0; i < member.biographyCount; i++) {
        member.biography[i] = inputString(is, "Enter biography line (Latin letters, space or hyphen): ");
    }

    return is;
}

void CommissionMember::saveTextRecord(ostream& os) const {
    Human::saveTextRecord(os);
    os << ";" << commissionName << ";" << biographyCount;
    for (int i = 0; i < biographyCount; i++) {
        os << ";" << biography[i];
    }
}

void CommissionMember::saveBinaryRecord(ostream& os) const {
    Human::saveBinaryRecord(os);
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
}

void CommissionMember::loadFromText(istream& is) {
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
                
                // Parse CommissionMember data: commissionName;biographyCount;biography...
                nextPos = line.find(';', pos);
                if (nextPos != string::npos) {
                    commissionName = line.substr(pos, nextPos - pos);
                    pos = nextPos + 1;
                    
                    nextPos = line.find(';', pos);
                    if (nextPos != string::npos) {
                        string countStr = line.substr(pos, nextPos - pos);
                        istringstream css(countStr);
                        css >> biographyCount;
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
                    }
                }
            }
        }
    }
}

void CommissionMember::loadFromBinary(istream& is) {
    Human::loadFromBinary(is);
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
}

