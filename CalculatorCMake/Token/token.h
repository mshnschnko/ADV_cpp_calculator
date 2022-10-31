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
	double value;
	std::string name;
	char tokenID;
};