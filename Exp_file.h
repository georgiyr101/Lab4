#pragma once
#include "Exp.h"

class FileException : public Exp {
public:
    FileException(int errorCode, const std::string& errorMessage):Exp(errorCode, errorMessage){}
    ~FileException() = default;
};
