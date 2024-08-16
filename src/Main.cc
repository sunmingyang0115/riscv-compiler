#include "ast/Expressions.hh"
#include <iostream>
#include <memory>
#include <sstream>

int main(int argc, char *argv[]) {
    // std::string a = "123";
    AST::Expression* num = new AST::Literal("123");
    std::vector<AST::Expression *> v{num};

    AST::Do *d = new AST::Do{v};
    // std::cout << d->expressions.at(0);

    // AST::Literal *n = new AST::Literal(a);
    delete d;

}
