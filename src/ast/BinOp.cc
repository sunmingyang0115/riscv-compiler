#include "Expressions.hh"

BinOp::BinOp(Operator op, std::vector<Expression *> exprs)
: Expression{exprs}, m_op{op}
{}

BinOp::~BinOp(){}

void BinOp::accept(Visitor *v) { v->visit(this); }
