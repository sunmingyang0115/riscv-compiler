#include "Expressions.hh"
#include <string>

Variable::Variable(std::string name)
: m_name{name} {};
Variable::~Variable() {}
void Variable::accept(Visitor *v) { v->visit(this); }
