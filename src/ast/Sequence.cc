#include "Expressions.hh"

Sequence::Sequence(std::vector<Expression *> exprs)
: Expression{exprs}
{}

Sequence::~Sequence(){}

void Sequence::accept(Visitor *v) { v->visit(this); }
