#include "Parser.hh"
#include "Tokenizer.hh"
#include "../ast/Expressions.hh"
#include <vector>
#include "BracketUtil.hh"

std::string Parser::safePop()
{
    if (!m_tk.hasNext())
    {
        m_isValid = false;
        return "";
    }
    return m_tk.pop();
}

std::string Parser::safePeek()
{
    if (!m_tk.hasNext())
    {
        m_isValid = false;
        return "";
    }
    return m_tk.peek();
}

BinOp::Operator strToOp(std::string tk)
{
    if (tk == "+")  return BinOp::Operator::PLUS;
    if (tk == "-")  return BinOp::Operator::MINUS;
    if (tk == "*")  return BinOp::Operator::TIMES;
    if (tk == "/")  return BinOp::Operator::DIVIDE;
    if (tk == "=")  return BinOp::Operator::EQ;
    if (tk == ">")  return BinOp::Operator::GT;
    if (tk == "<")  return BinOp::Operator::LT;
    if (tk == ">=") return BinOp::Operator::GEQ;
    if (tk == "<=") return BinOp::Operator::LEQ;
    return BinOp::Operator::SIZE;
}

Parser::Parser(std::string s)
    : m_tk{s}, m_isValid{true} {}

Parser::~Parser() {}

Expression *Parser::build()
{
    Expression *res = parse();
    if (!m_isValid || m_tk.hasNext())
    {
        delete res;
        return nullptr;
    }
    return res;
}

Expression *Parser::parse()
{
    std::string open = safePop();
    if (isOpenBracket(open))
    {
        std::string token = safePop();
        Expression* res = parseExp(token);
        std::string close = safePop();
        if (!isMatchingBracketPairs(open, close))
        {
            m_isValid = false;
        }
        return res;
    }
    else
    {
        return parseLit(open);
    }
    
}

Expression *Parser::parseExp(std::string token)
{
    #ifdef DEBUG_PARSER
        std::cout << "exp : " << token << std::endl;
    #endif
    if (token == "seq")
    {
        std::vector<Expression *> v;
        while (!isCloseBracket(safePeek()))
        {
            v.push_back(parse());
        }
        return new Sequence(v);
    }
    BinOp::Operator binOpRes = strToOp(token);
    if (binOpRes != BinOp::Operator::SIZE)
    {
        std::vector<Expression *> v;
        while (!isCloseBracket(safePeek()))
        {
            v.push_back(parse());
        }
        return new BinOp(binOpRes, v);
    }
    else
    {
        m_isValid = false;
        return nullptr;
    }
}

Expression *Parser::parseLit(std::string token)
{
    #ifdef DEBUG_PARSER
        std::cout << "lit : " << token << std::endl;
    #endif
    return new Literal(std::atoi(token.c_str()));
}
