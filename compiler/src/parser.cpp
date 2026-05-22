#include "parser.h"
#include <vector>
#include <string>
#include <memory>
#include <variant>

bool Parser::check(TokenType type) const {
	if (!isAtEnd()) {
		return peek().type == type;
	}
	return false;
}

Token Parser::advance() {
	if (!isAtEnd()) {
		return tokens_[current_++];
	}
	return tokens_[current_];
}

bool Parser::isAtEnd() const {
	return peek().type == TokenType::EOF_TOKEN;
}

Token Parser::consume(TokenType type, const std::string& message) {
	if (check(type)) {
		return advance();
	}

	std::cerr << message << '\n';
}

Token Parser::peek() const {
	return tokens_[current_];
}

Token Parser::previous() const {
	return tokens_[current_ - 1];
}

int Parser::bindingPower(Token token) {
	switch (token.type) {
	case TokenType::EQUAL: return 5; // Assignment
	case TokenType::EQUAL_EQUAL:
	case TokenType::EXCLAMATION_EQUAL: return 10; // Equality
	case TokenType::LESS_EQUAL:
	case TokenType::GREATER_EQUAL:
	case TokenType::GREATER:
	case TokenType::LESS: return 20; // Comparison
	case TokenType::PLUS:
	case TokenType::MINUS: return 30; // ADD/SUB
	case TokenType::STAR:
	case TokenType::SLASH: return 40; // MUL/DIV
	case TokenType::EXCLAMATION: return 50; // Unary
	case TokenType::LEFT_PAREN: return 60; // Parenthesis
	}
}


bool Parser::match(std::initializer_list<TokenType> types) {
	for (TokenType type : types) {
		if (check(type)) {
			advance();
			return true;
		}
	}
	return false;
}

std::unique_ptr<Stmt> Parser::statement() {
	if (match({ TokenType::INT, TokenType::FLOAT, TokenType::VOID, TokenType::CHAR })) return varDeclaration();
	if (match({ TokenType::RETURN })) return retStatement();
	if (match({ TokenType::IF })) return ifStatement();
	if (match({ TokenType::WHILE })) return whileStatement();
	if (match({ TokenType::LEFT_BRACE })) return blockStatement();

	// expr;
	auto expr = parseExpr(0);
	consume(TokenType::SEMICOLON, "Expected ';' after expression.");
	
	return std::make_unique<ExprStmt>(
		std::move(expr)
	);
}

// return expr;
// return;
std::unique_ptr<Stmt> Parser::retStatement() {
	std::unique_ptr<Expr> value = nullptr;
	if (!check(TokenType::SEMICOLON)) {
		value = parseExpr(0);
	}

	consume(TokenType::SEMICOLON, "Expected ';' after return value.");

	return std::make_unique<RetStmt>(
		std::move(value)
	);
}

// if (condition) {} else {}
std::unique_ptr<Stmt> Parser::ifStatement() {
	consume(TokenType::LEFT_PAREN, "Expected '(' after 'if'.");
	auto condition = parseExpr(0);
	consume(TokenType::RIGHT_PAREN, "Expected ')' after condition.");

	auto branch = statement();

	std::unique_ptr<Stmt> elseBranch = nullptr;
	if (match({ TokenType::ELSE })) {
		elseBranch = statement();
	}

	return std::make_unique<IfStmt>(
		std::move(condition),
		std::move(branch),
		std::move(elseBranch)
	);
}

// while (condition) {}
std::unique_ptr<Stmt> Parser::whileStatement() {
	consume(TokenType::LEFT_PAREN, "Expected '(' after 'if'.");
	auto condition = parseExpr(0);
	consume(TokenType::RIGHT_PAREN, "Expected ')' after condition.");

	auto body = statement();

	return std::make_unique<WhileStmt>(
		std::move(condition),
		std::move(body)
	);
}

// int x = 34; int x;
std::unique_ptr<Stmt> Parser::varDeclaration() {
	Token name = consume(TokenType::IDENTIFIER, "Expected variable name.");
	std::unique_ptr<Expr> initializer = nullptr;
	if (match({ TokenType::EQUAL })) {
		initializer = parseExpr(0);
	}

	consume(TokenType::SEMICOLON, "Expected ';' after initializer.");

	return std::make_unique<VarDeclStmt>(
		name,
		std::move(initializer)
	);
}

// {statement; statement; statement;}
std::unique_ptr<Stmt> Parser::blockStatement() {
	std::vector<std::unique_ptr<Stmt>> stmts;
	while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
		stmts.push_back(statement());
	}

	consume(TokenType::RIGHT_BRACE, "Expected '}' after statements.");

	return std::make_unique<BlockStmt>(
		std::move(stmts)
	);
}

// 1 + 2 * 3   x == 
std::unique_ptr<Expr> Parser::parseExpr(int minBindingPower) {
	Token tok = advance();
	auto leftNode = nud(tok);

	while (bindingPower(peek()) > minBindingPower) {
		Token op = advance();

		leftNode = led(op, std::move(leftNode));
	}

	return leftNode;
}

std::unique_ptr<Expr> Parser::nud(Token token) {

}

std::unique_ptr<Expr> Parser::led(Token op, std::unique_ptr<Expr> left) {

}

