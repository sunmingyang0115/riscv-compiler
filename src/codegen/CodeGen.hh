#ifndef CODE_GEN_H
#define CODE_GEN_H
#include <string>
#include "../ast/Expressions.hh"

bool compile(std::string file, AST::Expression* ast);

#endif