#pragma once

#include "Solver.h"
#include "Exceptions.h"
#include "Tokens.h"
#include "Variables.h"
#include <iostream>


class Calculator {
public:
	std::string buffer;
	void start();
};
