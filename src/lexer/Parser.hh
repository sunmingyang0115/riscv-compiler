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
    Expression *parseExp();
    Expression *parseLit();
    Expression *parse();
    std::string safePop();
    std::string safePeek();
    Tokenizer m_tk;
    std::vector<std::string> m_bracketStack{};
    bool m_isValid{};

public:
    Parser(std::string input);
    ~Parser();
    Expression *build();
};

#endif