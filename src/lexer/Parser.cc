#include "Parser.hh"
#include "Tokenizer.hh"
#include "../ast/Expressions.hh"
#include <vector>
#include <sstream>
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
    if (tk == "+")
        return BinOp::Operator::PLUS;
    if (tk == "-")
        return BinOp::Operator::MINUS;
    if (tk == "*")
        return BinOp::Operator::TIMES;
    if (tk == "/")
        return BinOp::Operator::DIVIDE;
    if (tk == "=")
        return BinOp::Operator::EQ;
    if (tk == ">")
        return BinOp::Operator::GT;
    if (tk == "<")
        return BinOp::Operator::LT;
    if (tk == ">=")
        return BinOp::Operator::GEQ;
    if (tk == "<=")
        return BinOp::Operator::LEQ;
    return BinOp::Operator::SIZE;
}

std::string removeComments(std::string s)
{
    std::stringstream ss;
    int start = 0;
    for (int i = 0; i < s.length(); i++)
    {
        if (s.substr(i,2) == "|#")
        {
            start = i+2;
        }
        if (s.substr(i,2) == "#|")
        {
            ss << s.substr(start, i-start);
            start = i;
        }
    }
    ss << s.substr(start, s.length()-1-start);
    return ss.str();
}

Parser::Parser(std::string s)
    : m_isValid{true}, m_tk{removeComments(s)} {}

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
        Expression *res = parseExp(token);
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
    std::cout << "exp : " << token << "\n";
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
    else if (token == "set")
    {
        Expression *var = parse();
        Expression *val = parse();
        return new Set(var, val);
    }
    else if (token == "int")
    {
        Expression *var = parse();
        return new Declare(token, var);
    }
    else if (token == "while")
    {
        Expression *cond = parse();
        Expression *body = parseExp("seq");
        return new While(cond, body);
    }
    else if (token == "if")
    {
        Expression *cond = parse();
        Expression *ifthen = parse();
        Expression *ifelse = parse();
        return new If(cond, ifthen, ifelse);
    }
    else    // binOp
    {
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
}

// gpt code
bool isNumber(const std::string &s)
{
    try
    {
        size_t pos = 0;
        std::stoi(s, &pos);
        return pos == s.size(); // Ensure entire string was parsed
    }
    catch (...)
    {
        return false; // stoi throws if conversion fails
    }
}

Expression *Parser::parseLit(std::string token)
{
#ifdef DEBUG_PARSER
    std::cout << "lit : " << token << "\n";
#endif
    if (isNumber(token))
    {
        return new Literal(std::atoi(token.c_str()));
    }
    else
    {
        return new Variable(token);
    }
}
