#pragma once
#include <map>
#include <memory>
#include <queue>
#include <stack>

#include "../Error/error.h"
#include "../Token/token.h"
#include "../Operators/operator.h"

class eval {
public:
	eval() = default;
	double evalvate(const std::map<char, std::unique_ptr<baseOperator>>& operators, std::queue<token_t>& queueRPN);
};