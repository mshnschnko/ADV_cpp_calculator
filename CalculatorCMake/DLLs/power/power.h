#pragma once
#include "../../Operators/operator.h"
#include "../../PluginLoader/pluginLoader.h"

class power : public baseOperator {
public:
	power() {
		_unar = false;
		_associate = associate_t::RIGHT;
		_priority = 8;
		_operatorId = '^';
		_operatorName = "^";
	}
	virtual double execOperation(double lValue, double rValue, error& err) override {
		return pow(lValue, rValue);
	}
};