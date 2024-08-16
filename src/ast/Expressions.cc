#include "Expressions.hh"

AST::Do::~Do() {
    for (Expression *e : this->expressions) {
        delete e;
    }
}
