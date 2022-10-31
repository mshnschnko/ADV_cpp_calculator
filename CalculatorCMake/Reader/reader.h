#pragma once

#include <string>
#include <map>
#include <memory>
#include <queue>
#include <set>

#include "../Error/error.h"
#include "../Operators/operator.h"
#include "../Token/token.h"

class reader {
public:
	reader() = default;
	void readString(const std::map<char, std::unique_ptr<baseOperator>>& operators, const std::string& strToParse);
	std::queue<token_t> getTokenQueue() { return _tokenQueue; }
private:
	std::set<std::pair<std::string, char>> _opersSet; // set of operators' names and IDs
	std::queue<token_t> _tokenQueue;
	void opersNames(const std::map<char, std::unique_ptr<baseOperator>>& opers);
	token_t readFunc(const char* stringBegin);
};