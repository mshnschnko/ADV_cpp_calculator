#pragma once
#include "../../Operators/operator.h"
#include "../../PluginLoader/pluginLoader.h"

class sinus : public baseOperator {
public:
	sinus() {
		_unar = true;
		_associate = associate_t::LEFT;
		_priority = 9;
		_operatorId = 's';
		_operatorName = "sin";
	}
	virtual double execOperation(double lValue, double rValue, error& err) override {
		return sin(lValue);
	}
};