#include "Expressions.hh"

Function::Function(std::string name, std::string retType, Expression* args, Expression* body)
: m_name{name}, m_retType{retType}, Expression{{args, body}} {}

Function::~Function() {}

void Function::accept(Visitor *v) { v->visit(this); }
