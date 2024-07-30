#ifndef PARSER_H
#define PARSER_H
#include <string>

class Tokenizer;
class Expression;

class Parser
{
private:
    Expression *parseExp();
    Expression *parseLit(std::string s);
    Tokenizer* m_tk{};

public:
    Parser(std::string input);
    ~Parser();
    Expression *build();
};

#endif