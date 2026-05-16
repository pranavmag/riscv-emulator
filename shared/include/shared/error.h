# pragma once

#include <iostream>
#include <string>

struct ErrorHandling {
	bool hasError = false;

	void report(int line, const std::string& where, const std::string& message) {
		std::cerr << "[line " << line << "] Error at " << where << ": " << message << '\n';
	}

	void error(int line, const std::string& message) {
		report(line, "", message);
	}
};