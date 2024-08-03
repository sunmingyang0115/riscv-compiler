#include "Expressions.hh"

Set::Set(Expression *variable, Expression *value)
    : m_variable{variable}, m_value{value} {};

Set::~Set()
{
    delete m_variable;
    delete m_value;
}

Expression *Set::getVariable()
{
    return m_variable;
}
Expression *Set::getValue()
{
    return m_value;
}

void Set::visitChildren(Visitor *v)
{
    // m_variable->visitAll(v);
    m_value->visitAll(v);
}
void Set::accept(Visitor *v) { v->visit(this); }
void Set::reject(Visitor *v) { v->leave(this); }
