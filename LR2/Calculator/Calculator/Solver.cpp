#include "Solver.h"


ExpressionAnalyzer::ExpressionAnalyzer(std::vector<Lexeme>& raw_tokens) {
	this->raw_tokens = raw_tokens;
}

void ExpressionAnalyzer::analyze_prioritize() {
	try {
		if ((raw_tokens[1].getTokenType() == TokenType::assignment) && (raw_tokens[0].getTokenType() != TokenType::variable)) {
			throw AssignmentError();
		}
	}
	catch (std::out_of_range) {

	}
	int additional_priority = 0;
	int unclosed_parenthesis = 0;
	std::vector <Lexeme>::iterator it = raw_tokens.begin();
	while (it != raw_tokens.end()) {
		bool unary_minus_possible = true;
		bool operation_possible = true;
		if (it->getTokenType() == assignment) {
			if (it != ++raw_tokens.begin()) {
				throw AssignmentError();
			}
			unary_minus_possible = true;
			it->setPriority(OPERATOR_PRIORITY.at("=") + additional_priority);
		}		
		else if (it->getTokenType() == l_parenthesis) {
			additional_priority += OPERATOR_PRIORITY.at("(");
			unclosed_parenthesis++;
			unary_minus_possible = true;
			operation_possible = false;
		}
		else if (it->getTokenType() == r_parenthesis) {
			additional_priority += OPERATOR_PRIORITY.at(")");
			unclosed_parenthesis--;
			unary_minus_possible = false;
			operation_possible = true;
		}
		else if (it->getTokenType() == TokenType::function_delimiter) {
			unary_minus_possible = true;
			operation_possible = false;
		}
		else if (it->getTokenType() == operation) {
			if (++it == raw_tokens.end()) {
				--it;
				throw BinaryOperatorError();
			}
			if (it->getTokenValue() == "-") {				
				if (it == raw_tokens.begin()) {					
					it->setPriority(OPERATOR_PRIORITY.at("-u") + additional_priority);
					it->setTokenValue("-u");
					if ((++it)->getTokenType() == TokenType::operation) {
						--it;
						throw BinaryOperatorError();
					}
				}
				else {
					if (unary_minus_possible) {
						if ((++it)->getTokenType() == TokenType::operation) {
							--it;
							throw BinaryOperatorError();
						}
						it->setTokenValue("-u");
						it->setPriority(OPERATOR_PRIORITY.at("-u") + additional_priority);
					}
					else {
						if (!operation_possible) {
							throw BinaryOperatorError();
						}
						it->setPriority(OPERATOR_PRIORITY.at("-") + additional_priority);
					}
				}
				unary_minus_possible = false;				
			}
			else {
				if (!operation_possible) {
					throw BinaryOperatorError();
				}
				it->setPriority(OPERATOR_PRIORITY.at(it->getTokenValue()) + additional_priority);
				unary_minus_possible = true;
			}
			operation_possible = false;
		}
		else if (it->getTokenType() == TokenType::function) {
			operation_possible = true;
			Functions check_func;
			std::string func_type = check_func.func_type(it->getTokenValue());
			if (func_type == "NotFunction") {
				throw FunctionDoesntExist(it->getTokenValue());
			}
			else {
				auto current_it = it;
				int arg_count = 0;
				while (current_it != raw_tokens.end() || current_it->getTokenType() == TokenType::r_parenthesis) {
					if (arg_count == 0 && current_it->getTokenType() != TokenType::r_parenthesis) arg_count++;
					else if (current_it->getTokenType() == TokenType::function_delimiter) arg_count++;
					current_it++;
				}
				if (func_type == "Binary" && arg_count != 2) {
					throw FunctionWrongArgumentAmount(it->getTokenValue(), arg_count, 2);
				}
				else if (func_type == "Unary" && arg_count != 1) {
					throw FunctionWrongArgumentAmount(it->getTokenValue(), arg_count, 2);
				}
				current_it++;
			}
			it->setPriority(OPERATOR_PRIORITY.at("func") + additional_priority);
		}
		else if (it->getTokenType() == TokenType::other) {
			throw TokenUnresolvedException();
		}
		else {
			unary_minus_possible = false;
			operation_possible = true;
		}
		it++;
	}
	if (unclosed_parenthesis != 0) {
		throw NoCloseParenthesis();
	}
}

void ExpressionAnalyzer::finalize_tokens() {
	std::vector <Lexeme>::iterator it = raw_tokens.begin();
	while (it != raw_tokens.end()) {
		if (it->getTokenType() == TokenType::function_delimiter || it->getTokenType() == TokenType::l_parenthesis || it->getTokenType() == TokenType::r_parenthesis) {
			it = raw_tokens.erase(it);
		}
		else {
			it++;
		}
	}
}

std::vector <Lexeme> ExpressionAnalyzer::getTokens() {
	return this->raw_tokens;
}

ExpressionSolver::ExpressionSolver(std::vector<Lexeme> tokens) {
	this->tokens = tokens;
}

double ExpressionSolver::solve() {	
	std::vector<Lexeme>::iterator it = tokens.begin();	
	double value = 0;
	while (it != tokens.end()) {
		if (it->getTokenType() == TokenType::number || it->getTokenType() == TokenType::variable) {
			values_stack.push(*it);
		}
		else if (it->getTokenType() == TokenType::l_parenthesis) {
			operators_stack.push(*it);
			it++;
		}
		else if (it->getTokenType() == TokenType::r_parenthesis) {
			if (operators_stack.top().getTokenType() != TokenType::l_parenthesis) {
				ExpressionSolver::solve_operator();
			}
			else {
				operators_stack.pop();
				it++;
			}
		}
		else if(it->getTokenType() == TokenType::operation || it->getTokenType() == TokenType::function) {
			if (operators_stack.empty()) {
				operators_stack.push(*it);
				it++;
			}
			else {
				if (operators_stack.top().getTokenType() == TokenType::l_parenthesis || (it->getPriority() > operators_stack.top().getPriority())) {
					operators_stack.push(*it);
					it++;
				}
				else {
					ExpressionSolver::solve_operator();
				}
			}
		}
		else if (it->getTokenType() == TokenType::function_delimiter) {
			it++;
		}
		else if (it->getTokenType() == TokenType::assignment) {
			it++;
			Variables vars;
			double value = std::stod(values_stack.top().getTokenValue());
			values_stack.pop();
			vars.addOrChangeVar(values_stack.top().getTokenValue(), value);
		}
	}
	return std::stod(values_stack.top().getTokenValue());
}

void ExpressionSolver::solve_operator() {
	if (operators_stack.top().getTokenType() == TokenType::operation) {
		if (operators_stack.top().getTokenValue() == "-u") {
			values_stack.top().setTokenValue(std::to_string(-std::stod(values_stack.top().getTokenValue())));
			operators_stack.pop();
		}
		else {
			std::vector<double> args;
			for (int i = 0; i < 2; i++) {
				if (values_stack.top().getTokenType() == TokenType::number) {
					args.push_back(std::stod(values_stack.top().getTokenValue()));
				}
				else {
					Variables vars;
					args.push_back(vars.callVariable(values_stack.top().getTokenValue()));
				}
				values_stack.pop();
			}
			double result = 0;
			if (operators_stack.top().getTokenValue() == "-") {
				result = args[1] - args[0];
			}
			else if (operators_stack.top().getTokenValue() == "+") {
				result = args[1] + args[0];
			}
			else if (operators_stack.top().getTokenValue() == "/") {
				result = args[1] / args[0];
			}
			else if (operators_stack.top().getTokenValue() == "*") {
				result = args[1] * args[0];
			}
			else if (operators_stack.top().getTokenValue() == "^") {
				result = pow(args[1], args[0]);
			}
			operators_stack.pop();
			Lexeme new_value(std::to_string(result), TokenType::number, 0, 0);
		}
	}
	else if (operators_stack.top().getTokenType() == TokenType::function) {
		Functions func_solver;
		std::vector<double> args;
		if (func_solver.func_type(operators_stack.top().getTokenValue()) == "Binary") {
			for (int i = 0; i < 2; i++) {
				if (values_stack.top().getTokenType() == TokenType::number) {
					args.push_back(std::stod(values_stack.top().getTokenValue()));
				}
				else {
					Variables vars;
					args.push_back(vars.callVariable(values_stack.top().getTokenValue()));
				}
				values_stack.pop();
			}
		}
		else {
			if (values_stack.top().getTokenType() == TokenType::number) {
				args.push_back(std::stod(values_stack.top().getTokenValue()));
			}
			else {
				Variables vars;
				args.push_back(vars.callVariable(values_stack.top().getTokenValue()));
			}
			values_stack.pop();
		}
		double result = func_solver.count_func(operators_stack.top().getTokenValue(), args);
		operators_stack.pop();
		Lexeme new_value(std::to_string(result), TokenType::number, 0, 0);
	}
}