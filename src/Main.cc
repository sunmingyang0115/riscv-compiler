#include "parser/Lexer.hh"
#include <iostream>
#include <memory>
#include <sstream>

int main(int argc, char *argv[]) {
    // std::string a = "123";
    // AST::Expression* num = new AST::Literal("123");
    // std::vector<AST::Expression *> v{num};

    // AST::Do *d = new AST::Do{v};
    // // std::cout << d->expressions.at(0);
    
    // // AST::Literal *n = new AST::Literal(a);
    // delete d;

    // std::string a{"[int i = 23)"};
    // Tokenizer *tk = new Tokenizer{a};
    // while (tk->hasNext()) {
    //     std::cout << "|" << tk->next() << "|\n";
    // }

    Lexer* l = new Lexer{"(print 32) #| \n aming ; 123 |# \n (among 2) ; 123"};
    std::cout << l->parse() << "\n";
}
