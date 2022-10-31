#pragma once
#include <string>
#include "../Error/error.h"

class baseOperator {
public:
	char getId() const { return _operatorId; }
	std::string& getName() { return _operatorName; }
	int getPriority() const { return _priority; }
	bool isUnar() { return _unar; }
	bool isRightAssociate() const { return _associate == associate_t::RIGHT ? true : false; }
	virtual double execOperation(double lValue, double rValue, error& err) = 0;

protected:
	int _priority;
	char _operatorId;
	std::string _operatorName;
	bool _unar;

	enum class associate_t {
		RIGHT,
		LEFT
	};

	associate_t _associate;
};