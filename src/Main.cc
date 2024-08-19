#include "parser/Parser.hh"
#include <iostream>
#include <memory>
#include <sstream>

void printAST(AST::Expression* e) {
    if (AST::Do* ast = dynamic_cast<AST::Do *>(e)) {
        std::cout << "(do ";
        for (AST::Expression* exprs : ast->expressions) {
            printAST(exprs);
            if (ast->expressions.back() != exprs) {
                std::cout << " ";
            }
        }
        std::cout << ")";
    } else if (AST::Literal* ast = dynamic_cast<AST::Literal *>(e)) {
        std::cout << ast->value;
    } else if (AST::DeRef* ast = dynamic_cast<AST::DeRef *>(e)) {
        std::cout << "(deref ";
        printAST(ast->data);
        std::cout << ")";
    } else if (AST::While* ast = dynamic_cast<AST::While *>(e)) {
        std::cout << "(while ";
        printAST(ast->cond);
        std::cout << " ";
        printAST(ast->body);
        std::cout << ")";
    } else if (AST::If* ast = dynamic_cast<AST::If *>(e)) {
        std::cout << "(if ";
        printAST(ast->cond);
        std::cout << " ";
        printAST(ast->ifThen);
        std::cout << " ";
        printAST(ast->ifElse);
        std::cout << ")";
    } else if (AST::Ref* ast = dynamic_cast<AST::Ref *>(e)) {
        std::cout << "(ref " << ast->name << ")";
    }
    else {
        std::cout << "[nil]";
    }
}

int main(int argc, char *argv[]) {

    std::string s = "(do (while 1 (if n 0 1)))";
    AST::Expression* exp = parse(s);
    printAST(exp);
    std::cout << "\n";


}

