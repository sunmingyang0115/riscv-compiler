#include "Expressions.hh"

While::While(Expression* condition, Expression* body)
: Expression{{condition, body}} {}
While::~While() {}
void While::accept(Visitor *v) { v->visit(this); }
