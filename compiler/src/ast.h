# pragma once

#include "lexer.h"
#include <memory>
#include <vector>

struct ExprVisitor;

struct StmtVisitor;

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

	void accept(ExprVisitor& v) override;
};

// 90, 3.14, "hello world", etc
struct LiteralNode : Expr {
	Literal value;

	void accept(ExprVisitor& v) override;
};

// variable name
struct IdentifierNode : Expr {
	Token name;

	void accept(ExprVisitor& v) override;
};

// func(arg1, arg2, arg3, ...)
struct FuncCallNode : Expr {
	std::unique_ptr<Expr> funcName;
	std::vector<std::unique_ptr<Expr>> args;

	void accept(ExprVisitor& v) override;
};


// Recursive Descent Parsing
struct Stmt {
	virtual ~Stmt() = default;

	virtual void accept(StmtVisitor& v) = 0;
};

// int x = expr;
struct VarDeclStmt : Stmt {
	Token name;
	std::unique_ptr<Expr> initializer;

	void accept(StmtVisitor& v) override;
};

// return expr;
struct RetStmt : Stmt {
	std::unique_ptr<Expr> ret;

	void accept(StmtVisitor& v) override;
};

// if (expr) { body }, else is optional
struct IfStmt : Stmt {
	std::unique_ptr<Expr> condition;
	std::unique_ptr<Stmt> branch;
	std::unique_ptr<Stmt> elseBranch; // could be nullptr

	void accept(StmtVisitor& v) override;
};

// while (expr) { body }
struct WhileStmt : Stmt {
	std::unique_ptr<Expr> condition;
	std::unique_ptr<Stmt> body;

	void accept(StmtVisitor& v) override;
};

// { body }
struct BlockStmt : Stmt {
	std::vector<std::unique_ptr<Stmt>> body;

	void accept(StmtVisitor& v) override;
};

// expr;
struct ExprStmt : Stmt {
	std::unique_ptr<Expr> expr;

	void accept(StmtVisitor& v) override;
};








