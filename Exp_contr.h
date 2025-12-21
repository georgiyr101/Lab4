#pragma once
#include "Exp.h"

class ContainerException : public Exp {
public:
    ContainerException(int errorCode, const std::string& errorMessage): Exp(errorCode, errorMessage){}
    ~ContainerException() = default;
};