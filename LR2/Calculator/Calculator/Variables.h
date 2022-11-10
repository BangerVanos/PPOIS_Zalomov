#pragma once

#include <iostream>
#include <map>
#include <string>

std::map<std::string, double> vars;
const std::map<std::string, double> CONST_VARS{ {"PI", 3.141592}, {"pi", 3.141592}, {"E", 2.718281}, {"e", 2.718281} };


static class Variables {
public:
	void addOrChangeVar(std::string var_name, double var_value);
	double callVariable(std::string var_name);
};