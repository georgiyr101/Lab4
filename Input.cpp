#include "Exp_vvod.h"
#include "Input.h"
#include <iostream>
#include <limits>
using namespace std;

std::string inputString(std::istream& stream, const std::string& prompt)
{
    if (!prompt.empty()) { std::cout << prompt; }

    while (true)
    {
        try {
            std::string line;

            if (!std::getline(stream, line)) 
            {
                stream.clear();
                stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw InputException(1, "Error reading from stream.");
            }

            if (line.empty()) { throw InputException(20, "Empty input. Enter a string."); }

            for (char c : line) {
                if (!isLatinLetter(c) && c != ' ' && c != '-' && c != ',')
                {
                    throw InputException(21, "Invalid characters. Only Latin letters, space and hyphen are allowed.");
                }
            }

            return line;
        }
        catch (const InputException& e) {
            std::cout << e.what() << "\nTry again: ";
        }
    }
}

bool isUpperCase(char c) { return (c >= 'A' && c <= 'Z'); }

std::string inputName(std::istream& stream, const std::string& prompt)
{
    std::string name;
    bool valid = false;

    do {
        name = inputString(stream, prompt);

        try {
            if (name.empty()) {
                throw InputException(20, "Name cannot be empty.");
            }

            if (!isUpperCase(name[0])) {
                throw InputException(22, "First letter of name must be uppercase.");
            }

            for (int i = 1; i < name.length(); ++i) {
                if (name[i] == ' ' || name[i] == '-') {
                    if (i + 1 < name.length()) {
                        if (!isUpperCase(name[i + 1])) {
                            throw InputException(24, "After space or hyphen must be an uppercase letter.");
                        }
                        i++; 
                    }
                }
                else {
                    if (isUpperCase(name[i])) {
                        throw InputException(23, "Letters in the middle of word must be lowercase.");
                    }
                }
            }

            valid = true;
        }
        catch (const InputException& e) {
            std::cout << e.what() << "\nTry again: ";
            valid = false;
        }

    } while (!valid);

    return name;
}

bool isLatinLetter(char c) { return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')); }

