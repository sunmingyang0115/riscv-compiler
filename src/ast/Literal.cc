#include "Expressions.hh"

Literal::~Literal() {}
Literal::Literal(int number) : m_number{number} {};
void Literal::accept(Visitor *v) { v->visit(this); }
