// CalculatorCMake.cpp: определяет точку входа для приложения.
//
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include "CalculatorCMake.h"

void run() {
	calculator calc("..\\..\\..\\..\\CalculatorCMake\\DLLs\\plugins");
	const std::string exitString = "00";
	std::string enteredString;
	double res;
	std::cout << "Input expression (print '00' to close programm):" << std::endl;
	while (true) {
		error::getErrorInstance().updateError(error::errorType_t::NO_ERR, "No error");
		std::cout << "expression: ";
		std::getline(std::cin, enteredString);
		if (enteredString == exitString)
			break;
		enteredString.erase(std::remove(enteredString.begin(), enteredString.end(), ' '), enteredString.end());
		enteredString.erase(std::remove(enteredString.begin(), enteredString.end(), '\t'), enteredString.end());
		res = calc.execExpr(enteredString);
		if (error::getErrorInstance().getErrorType() != error::errorType_t::NO_ERR)
			std::cout << "ERROR: " << error::getErrorInstance().getErrorMessage() << std::endl;
		else
			std::cout << enteredString << " = " << res << std::endl;
	}
}

int main()
{
	run();
	_CrtDumpMemoryLeaks();
	return 0;
}