#include "Expressions.hh"
#include <string>

Variable::Variable(std::string name)
    : m_name{name} {};

Variable::~Variable() {};

std::string Variable::getName()
{
    return m_name;
}

void Variable::visitChildren(Visitor *v) {}
void Variable::accept(Visitor *v) { v->visit(this); }
void Variable::reject(Visitor *v) { v->leave(this); }
