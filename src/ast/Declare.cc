#include "Expressions.hh"

Declare::Declare(std::string type, Expression *name)
    : m_type{type}, m_variable{name} {};

Declare::~Declare()
{
    delete m_variable;
}

std::string Declare::getType()
{
    return m_type;
}
Expression *Declare::getVariable()
{
    return m_variable;
}

void Declare::visitChildren(Visitor *v)
{
    // m_name->visitAll(v);
}
void Declare::accept(Visitor *v) { v->visit(this); }
void Declare::reject(Visitor *v) { v->leave(this); }
