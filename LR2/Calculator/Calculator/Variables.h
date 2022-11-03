#pragma once

#include <iostream>
#include <map>
#include <string>


class Variables {
private:
	std::map<std::string, double> vars;
	const std::map<std::string, double> CONST_VARS{ {"PI", 3.141592}, {"pi", 3.141592}, {"E", 2.718281}, {"e", 2.718281}};
public:
	void addOrChangeVar(const std::string& var_name, double var_value);
	double callVariable(const std::string& var_name);
};