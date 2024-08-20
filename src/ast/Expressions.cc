#include "Expressions.hh"

AST::Do::~Do() {
    for (Expression *e : this->expressions) {
        delete e;
    }
    this->expressions.clear();
}

AST::RefFun::~RefFun() {
    for (Expression *e : this->arguments) {
        delete e;
    }
    this->arguments.clear();
}