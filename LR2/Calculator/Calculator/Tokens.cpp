#include "Tokens.h"


TokenBuffer::TokenBuffer(std::string buffer) {
	this->buffer = buffer;
}

void TokenBuffer::tokenDivider() {
	std::string temp_token = "";
	for (auto sym : this->buffer) {
		if (sym == '(' || sym == ')') {
			temp_token = sym;
			readyTokens.push_back(temp_token);
			temp_token = "";
		}
		else if (std::find(SEPS.begin(), SEPS.end(), sym) == SEPS.end()) {
			temp_token += sym;
		}
		else {
			readyTokens.push_back(temp_token);
			temp_token = "";
		}
	}
}

std::vector <std::string> TokenBuffer::GetReadyTokens() {
	return this->readyTokens;
}

TokenAnalyzer::TokenAnalyzer(const std::vector<std::string>& tokens) {
	this->tokens = tokens;
}

std::pair <std::string, token_type> TokenAnalyzer::readToken(const std::string& token) {
	const std::vector <std::string> FUNCS{"sin", "cos", "abs", "ln", "log", "sqrt", "pow", "max", "min"};
	std::pair <std::string, token_type> analyzed_token;
	analyzed_token.first = token;
	analyzed_token.second = other;
	const std::regex variable_pattern(R"([a-zA-Z]+\w*)");
	
	try {
		double util = std::stod(token);		
		analyzed_token.second = number;		
	}
	catch (...) {

	}
	if (std::find(FUNCS.begin(), FUNCS.end(), token) != FUNCS.end()) {
		analyzed_token.second = function;
	}
	else if (std::regex_match(token, variable_pattern)) {
		analyzed_token.second = variable;
	}	
	else if (token == "=") {
		analyzed_token.second = assignment;
	}
	else if (token == "(") {
		analyzed_token.second = l_parenthesis;
	}
	else if (token == ")") {
		analyzed_token.second = r_parenthesis;
	}
	else if (std::find(OPERATORS.begin(), OPERATORS.end(), token) != OPERATORS.end()) {
		analyzed_token.second = operation;
	}	
	return analyzed_token;
}

void TokenAnalyzer::readTokens() {
	for (auto token : this->tokens) {
		token_info.push_back(this->readToken(token));
	}
}

std::vector <std::pair <std::string, token_type>> TokenAnalyzer::GetTokenInfo() {
	return this->token_info;
}

FunctionAnalyzer::FunctionAnalyzer(const std::vector <std::pair <std::string, token_type>>& token_info) {
	this->token_info = token_info;
}

//Analyzing functions with their arguments
void FunctionAnalyzer::parse_function_arguments() {
	for (int i = 0; i < token_info.size(); i++) {
		std::pair <std::string, std::vector<std::string>> func_with_args;
		if (token_info[i].second == token_type::function) {
			func_with_args.first = token_info[i].first;
			std::vector<std::string> func_args;			
			for (int j = i + 1; j < token_info.size(); j++) {				
				if (token_info[j].second == token_type::r_parenthesis) break;
				func_args.push_back(token_info[j].first);
			}
			throw FunctionNoCloseParenthesis();
		}
	}
}

std::vector <std::pair <std::string, std::vector<std::string>>> FunctionAnalyzer::GetFuncNArguments() {
	return func_n_arguments;
}

//Solving functions to replace them with numbers in final token pull
FunctionSolver::FunctionSolver(const std::vector <std::pair <std::string, std::vector<std::string>>>& func_n_arguments) {
	this->func_n_arguments = func_n_arguments;
}

void FunctionSolver::solve() {
	for (auto func : func_n_arguments) {
		std::vector <double> doubled_args;
		for (auto arg : func.second) {
			doubled_args.push_back(std::stod(arg));
		}
		Functions func_solver;
		solved_funcs.push_back(std::to_string(func_solver.count_func(func.first, doubled_args)));
	}
}

std::vector <std::string> FunctionSolver::GetSolvedFunc() {
	return this->solved_funcs;
}




