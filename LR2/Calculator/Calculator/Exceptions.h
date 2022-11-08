#pragma once


#include <iostream>
#include <string>
#include <exception>



class BaseException : public std::exception {
protected:
	std::string exception_text;
public:
	std::string what();
};

class VariablesException : public BaseException {
public:
	VariablesException();
	VariablesException(const std::string& exception_text);	
};

class VariableAlreadyExists final : public VariablesException {
public:	
	VariableAlreadyExists(const std::string& var_name);
};

class VariableDoesntExist final : public VariablesException {
public:
	VariableDoesntExist(const std::string& var_name);
};

class FunctionException : public BaseException {
public:
	FunctionException();
	FunctionException(const std::string& exception_text);
};

class FunctionDoesntExist : public FunctionException {
public:
	FunctionDoesntExist(const std::string& func_name);
};

class FunctionWrongArgumentAmount final : public FunctionException {
public:
	FunctionWrongArgumentAmount(const std::string& func_name, int user_argument_amount, int argument_amount);
};

class FunctionNoCloseParenthesis final : public FunctionException {
public:
	FunctionNoCloseParenthesis();
};

class TokenException : public BaseException {
public:
	TokenException();
	TokenException(const std::string& exception_text);
};

class TokenUnresolvedException final : public TokenException {
	TokenUnresolvedException();
};