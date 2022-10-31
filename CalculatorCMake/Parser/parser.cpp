#include "../Error/error.h"
#include "parser.h"

bool parser::checkAssociate(const baseOperator* const op1, const baseOperator* const op2) {
	return (op1->getPriority() == op2->getPriority() && (op1->isRightAssociate())) ? op1->getPriority() > op2->getPriority() : op1->getPriority() >= op2->getPriority();
}

void parser::dropOperators(const std::map<char, std::unique_ptr<baseOperator>>& operators, const baseOperator* const op) {
	token_t token;
	while (!_stack2.empty() && checkAssociate(operators.at(_stack2.top().tokenID).get(), op) != 0) {
		token = _stack2.top();
		_stack2.pop();
		_stack1.push(token);
	}
}

parser::state_t parser::parsePrefix(const std::map<char, std::unique_ptr<baseOperator>>& operators, token_t& token) {
	baseOperator* tmpOper1;
	if (token.tokenType == tokenType_t::NUMBER) {
		_stack1.push(token);
		return state_t::SUFFIX;
	}
	else if (token.tokenType == tokenType_t::OPER && token.name == "(")
		_stack2.push(token);
	else if (token.tokenType == tokenType_t::OPER && token.name == "-") {
		token.tokenID = '!';
		_stack2.push(token);
	}
	else if (token.tokenType == tokenType_t::OPER) {
		tmpOper1 = operators.at(token.tokenID).get();
		if (tmpOper1->isUnar())
			_stack2.push(token);
		else {
			error::getErrorInstance().updateError(error::errorType_t::PARSE_ERR, "Wait for number, unar operator or '('");
			return state_t::END;
		}
	}
	return state_t::PREFIX;
}

parser::state_t parser::parseSuffix(const std::map<char, std::unique_ptr<baseOperator>>& operators, token_t& token) {
	if (token.tokenType == tokenType_t::OPER && token.name != "(") {
		dropOperators(operators, operators.at(token.tokenID).get());
		if (token.name != ")") {
			_stack2.push(token);
			return state_t::PREFIX;
		}
		else {
			if (_stack2.empty()) {
				error::getErrorInstance().updateError(error::errorType_t::PARSE_ERR, "'(' is missing");
				return state_t::END;
			}
			else {
				token = _stack2.top();
				_stack2.pop();
				return state_t::SUFFIX;
			}
		}
	}
	else {
		error::getErrorInstance().updateError(error::errorType_t::PARSE_ERR, "Wait for operation or ')'");
		return state_t::END;
	}
}

void parser::parseDone(const std::map<char, std::unique_ptr<baseOperator>>& operators) {
	dropOperators(operators, operators.at(')').get());
	if (!_stack2.empty()) {
		error::getErrorInstance().updateError(error::errorType_t::PARSE_ERR, "Right bracket");
		return;
	}
	while (!_stack1.empty()) {
		_stack2.push(_stack1.top());
		_stack1.pop();
	}
	while (!_stack2.empty()) {
		_queueRPN.push(_stack2.top());
		_stack2.pop();
	}
}

void parser::parseQueue(const std::map<char, std::unique_ptr<baseOperator>>& operators, std::queue<token_t>& tokens) {
	state_t parseState = state_t::PREFIX;
	token_t token;
	while (parseState != state_t::END) {
		if (parseState == state_t::PREFIX || parseState == state_t::SUFFIX) {
			if (tokens.empty()) {
				if (parseState == state_t::SUFFIX)
					parseState = state_t::DONE;
				else {
					error::getErrorInstance().updateError(error::errorType_t::PARSE_ERR, "Unexpected end of expression");
					parseState = state_t::END;
				}
			}
			else {
				token = tokens.front();
				tokens.pop();
			}
		}
		switch (parseState) {
		case state_t::PREFIX:
			parseState = parsePrefix(operators, token);
			break;
		case state_t::SUFFIX:
			parseState = parseSuffix(operators, token);
			break;
		case state_t::DONE:
			parseDone(operators);
			parseState = state_t::END;
			break;
		}
	}
}