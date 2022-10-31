#pragma once
#include <map>
#include <queue>
#include <memory>
#include <stack>
#include <string>

#include "../Token/token.h"
#include "../Operators/operator.h"

class parser {
public:
	parser() = default;
	void parseQueue(const std::map<char, std::unique_ptr<baseOperator>>& operators, std::queue<token_t>& tokens);
	std::queue<token_t> getQueueRPN() { return _queueRPN; }
private:
	std::stack<token_t> _stack1, _stack2;
	std::queue<token_t> _queueRPN;
	enum class state_t {
		PREFIX,
		SUFFIX,
		DONE,
		END
	};
	bool checkAssociate(const baseOperator* const op1, const baseOperator* const op2);
	void dropOperators(const std::map<char, std::unique_ptr<baseOperator>>& operators, const baseOperator* const op);
	state_t parsePrefix(const std::map<char, std::unique_ptr<baseOperator>>& operators, token_t& token);
	state_t parseSuffix(const std::map<char, std::unique_ptr<baseOperator>>& operators, token_t& token);
	void parseDone(const std::map<char, std::unique_ptr<baseOperator>>& operators);
};