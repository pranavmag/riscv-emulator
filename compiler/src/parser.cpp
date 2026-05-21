#include "parser.h"
#include <vector>
#include <string>
#include <memory>

std::unique_ptr<Stmt> Parser::statement() {
	if (match({ TokenType::INT, TokenType::FLOAT, TokenType::VOID, TokenType::CHAR })) return varDeclaration();
	if (match({ TokenType::RETURN })) return retStatement();
	if (match({ TokenType::IF })) return ifStatement();
	if (match({ TokenType::WHILE })) return whileStatement();
	if (match({ TokenType::LEFT_BRACE })) return blockStatement();

	auto expr = parseExpr(0);

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

