#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <vector>
#include "Tokenizer.hh"

// class Tokenizer;
class Expression;

class Parser
{
private:
    Expression *parseExp(std::string token);
    Expression *parseLit(std::string token);
    Expression *parse();
    std::string safePop();
    std::string safePeek();
    Tokenizer m_tk;
    bool m_isValid{};

public:
    Parser(std::string input);
    ~Parser();
    Expression *build();
};

#endif