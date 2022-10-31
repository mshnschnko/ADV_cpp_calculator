#include "reader.h"

token_t reader::readFunc(const char* stringBegin) {
	token_t returnToken;
	int i;
	for (auto& operName : _opersSet) {
		const char* c_operName = operName.first.c_str();
		for (i = 0; i < operName.first.length() && stringBegin[i] != 0; i++)
			if (c_operName[i] != stringBegin[i])
				break;
		if (i == operName.first.length()) {
			returnToken.tokenType = tokenType_t::OPER;
			returnToken.name = operName.first;
			returnToken.tokenID = operName.second;
			return returnToken;
		}
	}
	error::getErrorInstance().updateError(error::errorType_t::READ_ERR, "Unknown operator");
	return returnToken;
}

void reader::readString(const std::map<char, std::unique_ptr<baseOperator>>& operators, const std::string& strToParse) {
	opersNames(operators);
	token_t newToken;
	int i = 0;
	const char* str = strToParse.c_str(), * strBegin = strToParse.c_str();
	char* end;
	double res;
	while (*str != '\0' && str - strBegin < strToParse.length()) {
		if (*str >= '0' && *str <= '9') {
			res = strtod(str, &end);
			if (errno != 0 || end == str) {
				errno = 0;
				error::getErrorInstance().updateError(error::errorType_t::READ_ERR, "Bad number");
				return;
			}
			str = end;
			newToken.tokenType = tokenType_t::NUMBER;
			newToken.value = res;
			_tokenQueue.push(newToken);
		}
		else {
			newToken = readFunc(str);
			if (error::getErrorInstance().getErrorType() != error::errorType_t::NO_ERR)
				return;
			_tokenQueue.push(newToken);
			str = str + newToken.name.length();
		}
	}
}

void reader::opersNames(const std::map<char, std::unique_ptr<baseOperator>>& opers) {
	for (auto& elem : opers)
		if (elem.second->getId() != '!')
			_opersSet.emplace(std::pair<std::string, char>(elem.second->getName(), elem.second->getId()));
}