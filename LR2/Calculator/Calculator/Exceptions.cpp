#include "Exceptions.h"


std::string BaseException::what() {
	return exception_text;
}

VariablesException::VariablesException() {
	exception_text = "Error. Variable error.";
}

VariablesException::VariablesException(const std::string& exception_text) {
	this->exception_text = exception_text;
}

VariableAlreadyExists::VariableAlreadyExists(const std::string& var_name) {
	exception_text = "Error. You've tried to add variable " + var_name + " which is protected. Try other name for variable.";
}

VariableDoesntExist::VariableDoesntExist(const std::string& var_name) {
	exception_text = "Error. You've tried to get " + var_name + " value. That variable doesn't exist. Create new one with that name.";
}

FunctionException::FunctionException() {
	exception_text = "Error. Function error.";
}

FunctionException::FunctionException(const std::string& exception_text) {
	this->exception_text = exception_text;
}

FunctionDoesntExist::FunctionDoesntExist(const std::string& func_name) {
	exception_text = "Error. You've tried to use function " + func_name + " which doesn't exist.";
}

FunctionWrongArgumentAmount::FunctionWrongArgumentAmount(const std::string& func_name, int user_argument_amount, int argument_amount) {
	exception_text = "Error. Function " + func_name + " takes " + std::to_string(argument_amount) + ", but you've passed " + std::to_string(user_argument_amount);
}

TokenException::TokenException() {
	exception_text = "Error. Token error.";
}

TokenException::TokenException(const std::string& exception_text) {
	this->exception_text = exception_text;
}

TokenUnresolvedException::TokenUnresolvedException() {
	exception_text = "Unresolved token type.";
}



