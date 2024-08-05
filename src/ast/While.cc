#include "Expressions.hh"

While::While(Expression* condition, Expression* body)
    : m_condition{condition}, m_body{body} {};

While::~While()
{
    delete m_condition;
    delete m_body;
}

Expression *While::getCondition()
{
    return m_condition;
}
Expression *While::getBody()
{
    return m_body;
}

void While::visitChildren(Visitor *v)
{
    m_condition->visitAll(v);
    m_body->visitAll(v);
}
void While::accept(Visitor *v) { v->visit(this); }
void While::reject(Visitor *v) { v->leave(this); }
