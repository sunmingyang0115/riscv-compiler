#include "Parser.hh"
#include "Tokenizer.hh"
#include "../ast/Expressions.hh"
#include <vector>

std::string OPEN_BRACKETS[3] = {"(", "[", "{"};
std::string CLOSE_BRACKETS[3] = {")", "]", "}"};

std::string Parser::safePopTokenizer()
{
    if (!m_tk.hasNext())
    {
        m_isValid = false;
        return "";
    }
    return m_tk.getNext();
}

Parser::Parser(std::string s)
    : m_tk{s}, m_isValid{true} {}

Parser::~Parser()
{
}

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
    std::string s = safePopTokenizer();
    for (int i = 0; i < OPEN_BRACKETS->length(); i++)
    {
        if (s == OPEN_BRACKETS[i])
        {
            m_bracketStack.push_back(s);
            Expression *res = parseExp();
            m_isValid = (safePopTokenizer() == CLOSE_BRACKETS[i]) && m_isValid;
            m_bracketStack.pop_back();
            return res;
        }
    }

    return parseLit(s);
}

Expression *Parser::parseExp()
{
    std::string s = safePopTokenizer();

    if (s == "+")
    {
        Expression *a = parse();
        Expression *b = parse();
        return new BinOp(BinOp::Operator::PLUS, a, b);
    }
    else if (s == "-")
    {
        Expression *a = parse();
        Expression *b = parse();
        return new BinOp(BinOp::Operator::MINUS, a, b);
    }
    else if (s == "*")
    {
        Expression *a = parse();
        Expression *b = parse();
        return new BinOp(BinOp::Operator::TIMES, a, b);
    }
    else if (s == "/")
    {
        Expression *a = parse();
        Expression *b = parse();
        return new BinOp(BinOp::Operator::DIVIDE, a, b);
    }
    else if (s == "seq")
    {
        std::vector<Expression *> seq;
        //  = new std::vector<Expression*>();
        seq.push_back(parse());
        seq.push_back(parse());
        return new Sequence(seq);
    }
    else if (s == "int")
    {
        Expression *var = parse();
        return new Declare("int", var);
    }
    else if (s == "set")
    {
        Expression *var = parse();
        Expression *value = parse();
        return new Set(var, value);
    }
    m_isValid = false;
    return nullptr;
}

bool isNumber(const std::string &s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it))
        ++it;
    return !s.empty() && it == s.end();
}

Expression *Parser::parseLit(std::string token)
{
    if (isNumber(token))
    {
        return new Literal(std::atoi(token.c_str()));
    }
    else
    {
        return new Variable(token);
    }
}
