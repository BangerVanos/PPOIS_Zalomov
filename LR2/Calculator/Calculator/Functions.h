#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stdarg.h>


class Functions {
private:
	const std::vector<std::string> UNARY_FUNCS{"sin", "cos", "abs", "ln", "log", "sqrt"};
	const std::vector<std::string> BINARY_FUNCS{ "pow", "max", "min" };
public:
	double count_func(const std::string& func_name, int arg_count, double first_arg, ...);
};
