#include "eval.h"

double eval::evalvate(const std::map<char, std::unique_ptr<baseOperator>>& operators, std::queue<token_t>& queueRPN) {
	std::stack<token_t> tokens;
	token_t token, tokenNum1, tokenNum2;
	baseOperator* tmpOper;
	while (!queueRPN.empty()) {
		token = queueRPN.front();
		queueRPN.pop();
		if (token.tokenType == tokenType_t::NUMBER)
			tokens.push(token);
		else {
			tmpOper = operators.at(token.tokenID).get();
			if (!tmpOper->isUnar()) {
				tokenNum2 = tokens.top();
				tokens.pop();
			}
			tokenNum1 = tokens.top();
			tokens.pop();
			tokenNum1.value = tmpOper->execOperation(tokenNum1.value, tokenNum2.value, error::getErrorInstance());
			if (error::getErrorInstance().getErrorType() != error::errorType_t::NO_ERR)
				return -1;
			tokens.push(tokenNum1);
		}
	}
	tokenNum1 = tokens.top();
	tokens.pop();
	if (!tokens.empty()) {
		error::getErrorInstance().updateError(error::errorType_t::PARSE_ERR, "opers is not ended in eval");
		return 0;
	}
	return tokenNum1.value;
}