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

AST::Cond::~Cond() {
    for (Expression *e : this->conds) {
        delete e;
    }
    for (Expression *e : this->thens) {
        delete e;
    }
    this->conds.clear();
    this->thens.clear();
}