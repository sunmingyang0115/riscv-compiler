#include "Expressions.hh"

BinOp::BinOp(Operator op, std::vector<Expression *> vals)
: Expression{vals}, m_op(op)
{}

BinOp::~BinOp(){}

void BinOp::accept(Visitor *v) { v->visit(this); }
