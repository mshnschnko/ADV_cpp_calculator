#pragma once
#include <string>

class error {
public:
	enum class errorType_t {
		NO_ERR,
		OPER_ERR,
		EVAL_ERR,
		READ_ERR,
		PARSE_ERR
	};
	static error& getErrorInstance() {
		static error err;
		return err;
	}
	error(error const&) = delete;
	error(error&&) = delete;
	errorType_t getErrorType() { return _errorType; }
	std::string getErrorMessage() { return _errorMessage; }
	void updateError(errorType_t errorType, std::string const& errorMessage) {
		_errorType = errorType;
		_errorMessage = errorMessage;
	}
	void updateError(errorType_t errorType, std::string&& errorMessage) {
		_errorType = errorType;
		_errorMessage = std::move(errorMessage);
	}
private:
	error() = default;
	errorType_t _errorType = errorType_t::NO_ERR;
	std::string _errorMessage = "";
};