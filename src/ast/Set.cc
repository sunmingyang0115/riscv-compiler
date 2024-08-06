#include "Expressions.hh"

Set::Set(Expression *variable, Expression *value)
: Expression{{variable, value}} {}
Set::~Set() {}
void Set::accept(Visitor *v) { v->visit(this); }
