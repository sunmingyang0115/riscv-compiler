#include "parser/Parser.hh"
#include <iostream>
#include <memory>
#include <sstream>
#include "codegen/CodeGen.hh"
#include <fstream>

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
        std::cout << "(lit " << ast->value << ")";
    } else if (AST::DeRef* ast = dynamic_cast<AST::DeRef *>(e)) {
        std::cout << "(deref ";
        printAST(ast->data);
        std::cout << ")";
    } else if (AST::AddrOf* ast = dynamic_cast<AST::AddrOf *>(e)) {
        std::cout << "(addrOf ";
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
    } else if (AST::RefVar* ast = dynamic_cast<AST::RefVar *>(e)) {
        std::cout << "(ref " << ast->name << ")";
    } else if (AST::DefFun *ast = dynamic_cast<AST::DefFun *>(e)) {
        std::cout << "(def-fun " << ast->returnType << " " << ast->name << " [";
        for (int i = 0; i < ast->argNames.size(); i++) {
            std::cout << "(" << ast->argTypes.at(i) << " " << ast->argNames.at(i) << ")";
            if (ast->argNames.back() != ast->argNames.at(i)) {
                std::cout << " ";
            }
        }
        std::cout << "] ";
        printAST(ast->body);
        std::cout << ")";
    }
    else if (AST::DefVar *ast = dynamic_cast<AST::DefVar *>(e)) {
        std::cout << "(def-var " << ast->dataType << " " << ast->name << ")";
    } else if (AST::Bin *ast = dynamic_cast<AST::Bin *>(e)) {
        std::cout << "(bin " << ast->op << " ";
        printAST(ast->left);
        std::cout << " ";
        printAST(ast->right);
        std::cout << ")";
    } else if (AST::Set *ast = dynamic_cast<AST::Set *>(e)) {
        std::cout << "(set ";
        printAST(ast->data);
        std::cout << " ";
        printAST(ast->value);
        std::cout << ")";
    }
    else {
        std::cout << "[nil]";
    }
}

int main(int argc, char *argv[]) {

    std::ifstream t{"../test/main.rkt"};
    std::stringstream buffer;
    buffer << t.rdbuf();
    std::string s = buffer.str();
    
    AST::Expression* exp = parse(s);
    printAST(exp);
    compile("../test/rv32gtest.s", exp);
    delete exp;

}

