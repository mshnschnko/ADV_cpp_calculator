#pragma once
#include <iostream>
#include <string>

enum class tokenType_t {
	OPER,
	NUMBER
};

class token_t {
public:
	tokenType_t tokenType;
	double value = 0;
	std::string name;
	char tokenID;
};