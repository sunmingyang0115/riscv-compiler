#include "Expressions.hh"

Literal::~Literal() {}
Literal::Literal(int number) : m_number{number} {};
void Literal::visitChildren(Visitor* v) {}
void Literal::accept(Visitor* v) {v->visit(this);}
void Literal::leave(Visitor* v) {v->leave(this);}
