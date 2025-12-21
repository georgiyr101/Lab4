#pragma once
#include <iostream>
#include <sstream>
#include <limits>
#include <string>
#include "Exp_vvod.h"

template <typename T>
T inputNumber(std::istream& stream,
    T lowerBound,
    T upperBound,
    const std::string& prompt)
{
    if (!prompt.empty()) { std::cout << prompt; }

    while (true)
    {
        try {
            std::string line;

            if (!std::getline(stream, line)) {
                stream.clear();
                stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw InputException(1, "Error reading from stream.");
            }

            if (line.empty()) {
                throw InputException(0, "Empty input. Enter a number");
            }

            std::istringstream converter(line);
            T value;

            if (!(converter >> value)) {
                throw InputException(2, "Expected a number, got: " + line);
            }

            char extra;
            if (converter >> extra) {
                throw InputException(3, "Number contains extra characters.");
            }

            if (value < lowerBound || value > upperBound) {
                throw InputException(4, "Number is out of allowed range.");
            }

            return value;
        }
        catch (const InputException& e) {
            std::cout << e.what() << "\nTry again: ";
        }
    }
}

std::string inputString(std::istream& stream, const std::string& prompt);

bool isUpperCase(char c);

bool isLatinLetter(char c);

std::string inputName(std::istream& stream, const std::string& prompt);