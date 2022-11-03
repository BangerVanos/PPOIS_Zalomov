#pragma once

#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <utility>
#include <string>
#include <regex>

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
	std::vector <char> SEPS{ ' ', '\n', ',' };
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
