#pragma once
#include "../../Operators/operator.h"
#include "../../PluginLoader/pluginLoader.h"

class cosinus : public baseOperator {
public:
	cosinus() {
		_unar = true;
		_associate = associate_t::LEFT;
		_priority = 9;
		_operatorId = 'c';
		_operatorName = "cos";
	}
	virtual double execOperation(double lValue, double rValue, error& err) override {
		return cos(lValue);
	}
};