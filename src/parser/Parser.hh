#ifndef PARSER_H
#define PARSER_H
#include "../ast/Expressions.hh"
#include "../error/ErrorHandler.hh"
#include <string>

AST::Expression *parse(std::string &raw);

#endif