#pragma once
#include "../../Operators/operator.h"
#include "../../PluginLoader/pluginLoader.h"

class logarithm : public baseOperator {
public:
	logarithm() {
		_unar = true;
		_associate = associate_t::LEFT;
		_priority = 9;
		_operatorId = 'l';
		_operatorName = "log";
	}
	virtual double execOperation(double lValue, double rValue, error& err) override {
		return log(lValue);
	}
};