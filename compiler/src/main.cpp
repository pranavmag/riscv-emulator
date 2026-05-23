#include "shared/error.h"
#include "lexer.h"
#include "parser.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

ErrorHandling errorHandler;

void run(const std::string& source, ErrorHandling& errorHandler);

void runFile(const std::string& filePath, ErrorHandling& errorHandler) {
	std::ifstream file(filePath);
	if (!file) {
		std::cerr << "Could not open file: " << filePath << '\n';
		std::exit(1);
	}

	std::ostringstream buffer;
	buffer << file.rdbuf();
	run(buffer.str(), errorHandler);
	if (errorHandler.hasError) {
		std::exit(2);
	}
}

void runPrompt(ErrorHandling& errorHandler) {
	std::string userInput{};
	while (true) {
		std::cout << "> ";
		if (!std::getline(std::cin >> std::ws, userInput)) {
			break;
		}
		run(userInput, errorHandler);
		errorHandler.hasError = false;
	}
}

void run(const std::string& source, ErrorHandling& errorhandling) {
	Scanner scanner(source, errorhandling);
	std::vector<Token> tokens = scanner.scanTokens();

	Parser parser(tokens, errorhandling);
	std::vector<std::unique_ptr<Stmt>> code = parser.parseCode();
}


int main(int argc, char* argv[]) {
	if (argc > 2) {
		std::cerr << "Too many arguments\n";
    }
	else if (argc == 2) {
		runFile(argv[1], errorHandler);
	}
	else {
		runPrompt(errorHandler);
	}
}