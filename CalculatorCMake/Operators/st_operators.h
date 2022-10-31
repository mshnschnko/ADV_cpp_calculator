#pragma once
#include "operator.h"

class addOperator : public baseOperator {
public:
	addOperator() {
		_unar = false;
		_associate = associate_t::LEFT;
		_operatorId = '+';
		_operatorName = "+";
		_priority = 5;
	}
	double execOperation(double lValue, double rValue, error& err) override {
		return lValue + rValue;
	}
};

class substructOperator : public baseOperator {
public:
	substructOperator() {
		_unar = false;
		_associate = associate_t::LEFT;
		_operatorId = '-';
		_operatorName = "-";
		_priority = 5;
	}
	double execOperation(double lValue, double rValue, error& err) override {
		return lValue - rValue;
	}
};

class multiplyOperator : public baseOperator {
public:
	multiplyOperator() {
		_unar = false;
		_associate = associate_t::LEFT;
		_operatorId = '*';
		_operatorName = "*";
		_priority = 6;
	}
	double execOperation(double lValue, double rValue, error& err) override {
		return lValue * rValue;
	}
};

class divideOperator : public baseOperator {
public:
	divideOperator() {
		_unar = false;
		_associate = associate_t::LEFT;
		_operatorId = '/';
		_operatorName = "/";
		_priority = 6;
	}
	double execOperation(double lValue, double rValue, error& err) override {
		if (rValue == 0) {
			err.updateError(error::errorType_t::EVAL_ERR, "ERROR: cannot be divided by zero");
			return -1;
		}
		return lValue / rValue;
	}
};

class unarMinusOperator : public baseOperator {
public:
	unarMinusOperator() {
		_unar = true;
		_associate = associate_t::LEFT;
		_operatorId = '!';
		_operatorName = "-";
		_priority = 7;
	}
	double execOperation(double lValue, double rValue, error& err) override {
		return -1.0 * rValue;
	}
};

class leftBracket : public baseOperator {
public:
	leftBracket() {
		_unar = false;
		_associate = associate_t::LEFT;
		_operatorId = '(';
		_operatorName = "(";
		_priority = 0;
	}
	double execOperation(double lValue, double rValue, error& err) override {
		err.updateError(error::errorType_t::EVAL_ERR, "ERROR: '(' is not operator, it is a priority symbol");
		return -1;
	}
};

class rightBracket : public baseOperator {
public:
	rightBracket() {
		_unar = false;
		_associate = associate_t::LEFT;
		_operatorId = ')';
		_operatorName = ")";
		_priority = 1;
	}
	double execOperation(double lValue, double rValue, error& err) override {
		err.updateError(error::errorType_t::EVAL_ERR, "ERROR: ')' is not operator, it is a priority symbol");
		return -1;
	}
};