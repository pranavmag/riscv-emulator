# pragma once

#include "ast.h"
#include <variant>
#include <string>

struct ExprVisitor {
	// visitBinaryOp, visitUnaryOp()

	virtual ~ExprVisitor() = default;

	virtual int visitBinaryOp(BinaryOpNode& n) = 0;
	virtual int visitUnaryOp(UnaryOpNode& n) = 0;
	virtual Literal visitLiteralNode(LiteralNode& n) = 0;
	virtual Token visitIdentifierNode(IdentifierNode& n) = 0;
	virtual int visitFuncCallNode(FuncCallNode& n) = 0;


};

struct StmtVisitor {
	virtual ~StmtVisitor() = default;

	virtual void visitVarDecl(VarDeclStmt& n) = 0;
	virtual void visitRet(RetStmt& n) = 0;
	virtual void visitIf(IfStmt& n) = 0;
	virtual void visitWhile(WhileStmt& n) = 0;
	virtual void visitBlock(BlockStmt& n) = 0;
	virtual void visitExpr(ExprStmt& n) = 0;
};

