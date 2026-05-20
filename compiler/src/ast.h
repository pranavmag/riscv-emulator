# pragma once

#include "lexer.h"
#include <memory>
#include <vector>

struct ExprVisitor;

// Pratt Parsing
struct Expr {
	virtual ~Expr() = default;

	virtual void accept(ExprVisitor& v) = 0;
};

// a + b, a * b, a == b, etc.
struct BinaryOpNode : Expr {
	// left node, right node, operator
	std::unique_ptr<Expr> left;
	std::unique_ptr<Expr> right; 
	Token op;
	void accept(ExprVisitor& v) override;
};

// !x, -x, etc.
struct UnaryOpNode : Expr {
	Token op;
	std::unique_ptr<Expr> operand;
};

// 90, 3.14, "hello world", etc
struct LiteralNode : Expr {
	Literal value;
};

// variable name
struct IdentifierNode : Expr {
	Token name;
};

// func(arg1, arg2, arg3, ...)
struct FuncCallNode : Expr {
	std::unique_ptr<Expr> funcName;
	std::vector<std::unique_ptr<Expr>> args;
};


// Recursive Descent Parsing
struct Stmt {
	virtual ~Stmt() = default;
};

// int x = expr;
struct VarDeclStmt : Stmt {
	Token name;
	std::unique_ptr<Expr> initializer;
};

// return expr;
struct RetStmt : Stmt {
	std::unique_ptr<Expr> ret;
};

// if (expr) { body }, else is optional
struct IfStmt : Stmt {
	std::unique_ptr<Expr> condition;
	std::unique_ptr<Stmt> branch;
	std::unique_ptr<Stmt> elseBranch; // could be nullptr
};

// while (expr) { body }
struct WhileStmt : Stmt {
	std::unique_ptr<Expr> condition;
	std::unique_ptr<Stmt> body;
};

// { body }
struct BlockStmt : Stmt {
	std::vector<std::unique_ptr<Stmt>> body;
};

// expr;
struct ExprStmt : Stmt {
	std::unique_ptr<Expr> expr;
};








