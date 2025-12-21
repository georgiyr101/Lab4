#pragma once
#include "Exp.h"

class InputException : public Exp
{
public:
	InputException(int errorCode, const std::string& errorMessage) : Exp(errorCode, errorMessage){}
	~InputException() = default;
};
