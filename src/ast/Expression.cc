#include "Expressions.hh"

void Expression::visitAll(Visitor *v)
{
    accept(v);
    visitChildren(v);
    leave(v);
}
Expression::~Expression() {}
