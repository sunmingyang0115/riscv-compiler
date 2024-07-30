#include "Parser.hh"
#include "Tokenizer.hh"
#include "../ast/Expressions.hh"

Parser::Parser(std::string s)
    : m_tk{new Tokenizer(s)} {}

Parser::~Parser()
{
    delete m_tk;
}

Expression *Parser::build()
{
    std::string s = m_tk->getNext();
    if (s == "(")
    {
        Expression *res = parseExp();
        m_tk->getNext(); // skip )
        return res;
    }
    else
    {
        return parseLit(s);
    }
}

Expression *Parser::parseExp()
{
    std::string s = m_tk->getNext();

    if (s == "+")
    {
        Expression *a = build();
        Expression *b = build();
        return new BinOp(BinOp::Operator::PLUS, a, b);
    }
    else if (s == "-")
    {
        Expression *a = build();
        Expression *b = build();
        return new BinOp(BinOp::Operator::MINUS, a, b);
    }
    else if (s == "*")
    {
        Expression *a = build();
        Expression *b = build();
        return new BinOp(BinOp::Operator::TIMES, a, b);
    }
    else if (s == "/")
    {
        Expression *a = build();
        Expression *b = build();
        return new BinOp(BinOp::Operator::DIVIDE, a, b);
    }
    return nullptr;
}

Expression *Parser::parseLit(std::string token)
{
    return new Literal(std::atoi(token.c_str()));
}
