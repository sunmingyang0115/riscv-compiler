#include "Expressions.hh"

void Expression::visitAll(Visitor *v)
{
    accept(v);
    visitChildren(v);
    reject(v);
}
Expression::~Expression() {}
