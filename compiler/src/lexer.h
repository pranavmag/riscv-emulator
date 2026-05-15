# pragma once

#include <string>
#include <variant>
#include <vector>

enum TokenType {
	// Single-Character
	COMMA, SEMICOLON, LEFT_PAREN, RIGHT_PAREN,
	LEFT_BRACE, RIGHT_BRACE, PLUS, MINUS, STAR, SLASH, PERCENT,
	EXCLAMATION, EQUAL, GREATER, LESS, DOUBLE_QUOTE,

	// Double-Character
	EXCLAMATION_EQUAL,EQUAL_EQUAL,
	GREATER_EQUAL, LESS_EQUAL,

	// Literals
	STRING, NUMBER, IDENTIFIER,

	// keywords - Types
	INT, FLOAT, VOID, CHAR,
	
	// keywords - Control Flow/Loops
	IF, ELSE, WHILE, FOR, 
	
	PRINT,

	EOF_TOKEN
};

using Literal = std::variant<std::monostate, int, float, std::string>;

struct Token {
	TokenType type;
	std::string lexeme;
	Literal literal;
	int line;

	
	Token(TokenType type, std::string lex, std::variant< std::monostate, int, float, std::string> literal, int line) :
		type(type), lexeme(std::move(lex)), literal(std::move(literal)), line(line) {
	}
};

class Scanner {
private:
	std::string source_;
	std::vector<Token> tokens_;
	int start_ = 0;
	int current_ = 0;
	int line_ = 1;

public:
	Scanner(std::string source) : source_(std::move(source)) {
		std::vector<Token> tokens{};
	}

	bool isAtEnd() const {
		return current_ >= source_.size();
	}

	char advance() {
		return source_[current_++];
	}

	char peek() const {
		if (isAtEnd()) {
			return '\0';
		}
		return source_[current_];
		
	}

	char peekNext() const {
		if (current_ + 1 >= source_.size()) {
			return '\0';
		}
		return source_[current_ + 1];
	}

	bool match(char expected) {
		if (isAtEnd() || source_[current_] != expected) {
			return false;
		}
		++current_;
		return true;
	}

	void addToken(TokenType type);
	void addToken(TokenType type, Literal literal);
	std::vector<Token> scanTokens();
	void scanToken();
	void string();
	void number();
	void identifier();
};