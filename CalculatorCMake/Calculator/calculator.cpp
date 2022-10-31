#include "calculator.h"

#include <filesystem>
#include <iostream>

using defOp = baseOperator*(__cdecl*)(void);

void calculator::fillStandartOpersMap() {
	std::unique_ptr<baseOperator> oper = std::make_unique<addOperator>();
	_operatorsMap.emplace(std::make_pair(oper->getId(), std::move(oper)));
	oper = std::make_unique<substructOperator>();
	_operatorsMap.emplace(std::make_pair(oper->getId(), std::move(oper)));
	oper = std::make_unique<multiplyOperator>();
	_operatorsMap.emplace(std::make_pair(oper->getId(), std::move(oper)));
	oper = std::make_unique<divideOperator>();
	_operatorsMap.emplace(std::make_pair(oper->getId(), std::move(oper)));
	oper = std::make_unique<unarMinusOperator>();
	_operatorsMap.emplace(std::make_pair(oper->getId(), std::move(oper)));
	oper = std::make_unique<leftBracket>();
	_operatorsMap.emplace(std::make_pair(oper->getId(), std::move(oper)));
	oper = std::make_unique<rightBracket>();
	_operatorsMap.emplace(std::make_pair(oper->getId(), std::move(oper)));
}

void calculator::fillOpersFromOneDll(const std::string& dllPath) {
	HMODULE dll = LoadLibrary(dllPath.c_str());
	if (dll == nullptr) {
		std::cout << dllPath << ": Can't open dll" << std::endl;
		return;
	}
	defOp defOperFunc = (defOp)GetProcAddress(dll, "defOperator");
	if (defOperFunc == nullptr) {
		std::cout << dllPath << ": Can't find new operator initializer" << std::endl;
		FreeLibrary(dll);
		return;
	}
	_dlls.push_back(dll);
	std::unique_ptr<baseOperator> newOperator(defOperFunc());
	_operatorsMap.emplace(std::make_pair(newOperator->getId(), std::move(newOperator)));
	std::cout << dllPath << ": dll loaded" << std::endl;
}

void calculator::fillOpersFromDlls(const std::string& dllsPath) {
	std::filesystem::directory_iterator folder(dllsPath);
	std::cout << "DLL LOADER LOG:" << std::endl;
	std::cout << "Connect plagins from '" << dllsPath << "'" << std::endl;
	for (auto& file : folder) {
		if (file.path().extension().string() != ".dll")
			continue;
		fillOpersFromOneDll(file.path().string());
	}
	std::cout << "END LOG" << std::endl << std::endl;
}

calculator::calculator() {
	fillStandartOpersMap();
}

calculator::calculator(const std::string& dllPath) {
	fillStandartOpersMap();
	fillOpersFromDlls(dllPath);
}

double calculator::execExpr(const std::string& expr) {
	std::queue<token_t> tokenQueue, RPNqueue;
	reader read;
	parser pars;
	eval evalver;
	double res;
	read.readString(_operatorsMap, expr);
	if (error::getErrorInstance().getErrorType() != error::errorType_t::NO_ERR)
		return 0;
	pars.parseQueue(_operatorsMap, read.getTokenQueue());
	if (error::getErrorInstance().getErrorType() != error::errorType_t::NO_ERR)
		return 0;
	res = evalver.evalvate(_operatorsMap, pars.getQueueRPN());
	if (error::getErrorInstance().getErrorType() != error::errorType_t::NO_ERR)
		return 0;
	return res;
}

calculator::~calculator() {
	for (auto& dll : _dlls)
		FreeLibrary(dll);
}