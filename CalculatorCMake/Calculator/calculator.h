#pragma once
#include <windows.h>
#include <map>
#include <list>
#include <queue>
#include <stack>
#include <memory>

#include "../Error/error.h"
#include "../Operators/st_operators.h"
#include "../Token/token.h"
#include "../Reader/reader.h"
#include "../Parser/parser.h"
#include "../Eval/eval.h"

class calculator {
public:
	calculator();
	calculator(const std::string& dllPath);
	double execExpr(const std::string& expr);
	~calculator();
private:
	std::map<char, std::unique_ptr<baseOperator>> _operatorsMap;
	std::list<HMODULE> _dlls;
	void fillStandartOpersMap();
	void fillOpersFromDlls(const std::string& dllsPath);
	void fillOpersFromOneDll(const std::string& dllPath);
};