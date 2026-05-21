#include "visitor.h"

// Expressions
void BinaryOpNode::accept(ExprVisitor& v) {
	v.visitBinaryOpNode(*this);
}

void UnaryOpNode::accept(ExprVisitor& v) {
	v.visitUnaryOpNode(*this);
}

void LiteralNode::accept(ExprVisitor& v) {
	v.visitLiteralNode(*this);
}

void IdentifierNode::accept(ExprVisitor& v) {
	v.visitIdentifierNode(*this);
}

void FuncCallNode::accept(ExprVisitor& v) {
	v.visitFuncCallNode(*this);
}


// Statements
void VarDeclStmt::accept(StmtVisitor& v) {
	v.visitVarDecl(*this);
}

void RetStmt::accept(StmtVisitor& v) {
	v.visitRet(*this);
}

void IfStmt::accept(StmtVisitor& v) {
	v.visitIf(*this);
}

void WhileStmt::accept(StmtVisitor& v) {
	v.visitWhile(*this);
}

void BlockStmt::accept(StmtVisitor& v) {
	v.visitBlock(*this);
}

void ExprStmt::accept(StmtVisitor& v) {
	v.visitExpr(*this);
}







