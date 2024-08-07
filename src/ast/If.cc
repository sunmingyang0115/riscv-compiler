#include "Expressions.hh"

If::If(Expression* cond, Expression* ifthen, Expression* ifelse)
: Expression{{cond, ifthen, ifelse}} {}
If::~If() {}
void If::accept(Visitor *v) { v->visit(this); }
