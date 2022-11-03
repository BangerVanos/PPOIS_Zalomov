#include "Functions.h"
#include "Exceptions.h"


double Functions::count_func(const std::string& func_name, int arg_count, double first_arg, ...) {
	if ((std::find(BINARY_FUNCS.begin(), BINARY_FUNCS.end(), func_name) == BINARY_FUNCS.end()) || (std::find(UNARY_FUNCS.begin(), UNARY_FUNCS.end(), func_name) == UNARY_FUNCS.end())) {
		throw FunctionDoesntExist(func_name);
	}
	if (std::find(BINARY_FUNCS.begin(), BINARY_FUNCS.end(), func_name) != BINARY_FUNCS.end()) {
		if (arg_count != 2) {
			throw FunctionWrongArgumentAmount(func_name, arg_count, 2);
		}
		va_list argptr;
		va_start(argptr, arg_count);
		double second_arg = va_arg(argptr, double);
		if (func_name == "pow") {
			return pow(first_arg, second_arg);
		}
		else if (func_name == "min") {
			return first_arg < second_arg ? first_arg : second_arg;
		}
		else if (func_name == "max") {
			return first_arg > second_arg ? first_arg : second_arg;
		}
		va_end(argptr);
	}
	else {
		if (arg_count != 1) {
			throw FunctionWrongArgumentAmount(func_name, arg_count, 1);
		}
		if (func_name == "sin") {
			return sin(first_arg);
		}
		else if (func_name == "cos") {
			return cos(first_arg);
		}
		else if (func_name == "abs") {
			return abs(first_arg);
		}
		else if (func_name == "ln") {
			return log(first_arg);
		}
		else if (func_name == "log") {
			return log10(first_arg);
		}
		else if (func_name == "sqrt") {
			return sqrt(first_arg);
		}
	}
	throw FunctionException();
}