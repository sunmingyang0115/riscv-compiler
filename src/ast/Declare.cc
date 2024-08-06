#include "Expressions.hh"

Declare::Declare(std::string type, Expression *name)
: m_type{type}, Expression{{name}} {}
Declare::~Declare() {}
void Declare::accept(Visitor *v) { v->visit(this); };
