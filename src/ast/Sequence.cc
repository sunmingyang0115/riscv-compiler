#include "Expressions.hh"
#include <vector>
#include <iterator>

Sequence::Sequence(std::vector<Expression *> expressions)
    : m_expressions{expressions} {};

Sequence::~Sequence()
{
    for (std::vector<Expression *>::iterator i = m_expressions.begin(); i != m_expressions.end(); i++)
    {
        delete *i;
    }
    m_expressions.clear();
}

void Sequence::accept(Visitor *v) { v->visit(this); }
void Sequence::reject(Visitor *v) { v->leave(this); }
void Sequence::visitChildren(Visitor *v)
{
    for (Expression *&e : m_expressions)
    {
        e->visitAll(v);
    }
}
