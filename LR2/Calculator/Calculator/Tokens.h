#pragma once

#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <utility>
#include <string>
#include <regex>
#include "Functions.h"
#include "Exceptions.h"

enum token_type {
	number,
	operation,
	variable,
	function,
	assignment,
	r_parenthesis,
	l_parenthesis,
	other,
};

class TokenBuffer {
private:
	std::string buffer;
	std::vector <char> SEPS{ ' ', '\0', ',' };
	const std::vector <std::string> OPERATORS{ "+", "-", "*", "/", "^" };
	std::vector <std::string> readyTokens;
public:
	TokenBuffer(std::string buffer);
	void tokenDivider();
	std::vector <std::string> GetReadyTokens();
};


class TokenAnalyzer {
public:
	TokenAnalyzer(const std::vector<std::string>& tokens);
	void readTokens();
	std::vector <std::pair <std::string, token_type>> GetTokenInfo();
private:
	std::vector <std::string> tokens;
	std::pair <std::string, token_type> readToken(const std::string& token);
	std::vector <std::pair <std::string, token_type>> token_info;
	const std::vector <std::string> OPERATORS{"+", "-", "*", "/", "^"};
};


class FunctionAnalyzer {
public:
	FunctionAnalyzer(const std::vector <std::pair <std::string, token_type>>& token_info);
	void parse_function_arguments();
	std::vector <std::pair <std::string, std::vector<std::string>>> GetFuncNArguments();
private:
	std::vector <std::pair <std::string, token_type>> token_info;
	std::vector <std::pair <std::string, std::vector<std::string>>> func_n_arguments;
};

class FunctionSolver {
public:
	FunctionSolver(const std::vector <std::pair <std::string, std::vector<std::string>>>& func_n_arguments);
	void solve();
	std::vector <std::string> GetSolvedFunc();
private:
	std::vector <std::pair <std::string, std::vector<std::string>>> func_n_arguments;
	std::vector <std::string> solved_funcs;
};

class TokenFunctionReplacer {
public:
	TokenFunctionReplacer(const std::vector <std::pair <std::string, token_type>>& token_info);
	void replace_functions();
	std::vector <std::pair <std::string, token_type>> GetTokenInfo();
private:
	std::vector <std::pair <std::string, token_type>> token_info;
};
