#ifndef COMPILER_H
#define COMPILER_H
#include "../ast/Expressions.hh"
#include "RegAlloc.hh"
#include <unordered_map>
#include <sstream>

class Compiler {
private:
    std::stringstream builder;
    std::unordered_map<std::string, std::pair<AST::DataType, int>> varOffsetMap;
    RegAlloc allocator;
    int offsetFP;
    void push(int amount, std::string reg);
    void pull(int amount, std::string reg);

public:
    Compiler();
    ~Compiler();
    void compile(AST::Expression *ast);
    AST::DataType compileLV(AST::Expression *ast);
    bool finalize(std::string file);
};

#endif