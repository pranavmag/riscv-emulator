#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

struct ErrorHandling {
	bool hasError = false;

	void report(int line, const std::string& where, const std::string& message) {
		std::cerr << "[line " << line << "] Error at " << where << ": " << message << '\n';
	}

	void error(int line, const std::string& message) {
		report(line, "", message);
	}
};

ErrorHandling errorHandling;

void run(const std::string& source, ErrorHandling errorhandling);

void runFile(const std::string& filePath, ErrorHandling errorhandling) {
	std::ifstream file(filePath);
	if (!file) {
		std::cerr << "Could not open file: " << filePath << '\n';
		std::exit(1);
	}

	std::ostringstream buffer;
	buffer << file.rdbuf();
	run(buffer.str(), errorHandling);
	if (errorHandling.hasError) {
		std::exit(2);
	}
}

void runPrompt(ErrorHandling errorhandling) {
	std::string userInput{};
	while (true) {
		std::cout << "> ";
		if (!std::getline(std::cin >> std::ws, userInput)) {
			break;
		}
		run(userInput, errorhandling);
		errorHandling.hasError = false;
	}
}

int main(int argc, char* argv[]) {
	if (argc > 2) {
		std::cerr << "Too many arguments\n";
    }
	else if (argc == 2) {
		runFile(argv[1], errorHandling);
	}
	else {
		runPrompt(errorHandling);
	}
}