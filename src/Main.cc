#include "ast/Expressions.hh"
#include <iostream>
#include <memory>
#include <sstream>

int main(int argc, char *argv[]) {
    // std::string a = "123";
    AST::Literal *b = new AST::Literal{"123"};
    std::cout << b->value << "\n";
    delete b;
    // AST::Literal *n = new AST::Literal(a);

}
