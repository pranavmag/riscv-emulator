#include "visitor.h"

void BinaryOpNode::accept(ExprVisitor& v) {
	v.visitBinaryOp(*this);
}

