#pragma once


#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <map>
#include <stack>
#include "Functions.h"
#include "Tokens.h"
#include "Variables.h"
#include "Exceptions.h"


class ExpressionAnalyzer {
public:
	ExpressionAnalyzer(std::vector <Lexeme>& raw_tokens);
	void analyze_prioritize();
	void finalize_tokens();
	std::vector <Lexeme> getTokens();	
private:
	std::vector <Lexeme> raw_tokens;	
	const std::map <std::string, int> OPERATOR_PRIORITY{ {"=", 0}, {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}, {"-u", 3}, {"^", 4}, {"func", 5}, {"(", 0}, {")", 0}};	
};

class ExpressionSolver {
private:
	std::stack<Lexeme> operators_stack;
	std::stack<Lexeme> values_stack;
	std::vector<Lexeme> tokens;
	void solve_operator();
public:
	ExpressionSolver(std::vector<Lexeme> tokens);
	double solve();
};