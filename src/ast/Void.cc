#include "Expressions.hh"

Void::Void() {};
Void::~Void() {};
void Void::accept(Visitor* v) { v->visit(this); }
