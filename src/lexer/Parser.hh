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
    Expression *parseLit(std::string s);
    Expression *parse();
    std::string safePopTokenizer();
    Tokenizer m_tk;
    std::vector<std::string> m_bracketStack{};
    bool m_isValid{};

public:
    Parser(std::string input);
    ~Parser();
    Expression *build();
};

#endif