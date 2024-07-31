#include "Expressions.hh"

BinOp::BinOp(Operator op, Expression *left, Expression *right)
: m_op{op}, m_left{left}, m_right{right}
{}

BinOp::~BinOp()
{
    delete m_left;
    delete m_right;
}

void BinOp::visitChildren(Visitor* v)
{
    m_left->visitAll(v);
    m_right->visitAll(v);
}

void BinOp::accept(Visitor* v) {v->visit(this);}
void BinOp::reject(Visitor* v) {v->leave(this);}
