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
    std::string s = safePeek();
    for (int i = 0; i < OPEN_BRACKETS->length(); i++)
    {
        if (s == OPEN_BRACKETS[i])
        {
            m_bracketStack.push_back(safePop());
            Expression *res = parseExp();
            m_isValid = (safePop() == CLOSE_BRACKETS[i]) && m_isValid;
            m_bracketStack.pop_back();
            return res;
        }
    }

    return parseLit();
}

Expression *Parser::parseExp()
{
    std::string s = safePop();

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
    else if (s == "=")
    {
        Expression *a = parse();
        Expression *b = parse();
        return new BinOp(BinOp::Operator::EQ, a, b);
    }
    else if (s == "<")
    {
        Expression *a = parse();
        Expression *b = parse();
        return new BinOp(BinOp::Operator::LT, a, b);
    }
    else if (s == ">")
    {
        Expression *a = parse();
        Expression *b = parse();
        return new BinOp(BinOp::Operator::GT, a, b);
    }
    else if (s == "<=")
    {
        Expression *a = parse();
        Expression *b = parse();
        return new BinOp(BinOp::Operator::LEQ, a, b);
    }
    else if (s == ">=")
    {
        Expression *a = parse();
        Expression *b = parse();
        return new BinOp(BinOp::Operator::GEQ, a, b);
    }
    else if (s == "seq")
    {
        std::vector<Expression *> seq;
        while (!isCloseBracket(safePeek()) && safePeek() != "")
        {
            seq.push_back(parse());
        } 
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
    else if (s == "while")
    {
        Expression *cond = parse();
        std::vector<Expression *> seq;
        while (!isCloseBracket(safePeek()) && safePeek() != "")
        {
            seq.push_back(parse());
        } 
        Expression *body = new Sequence(seq);
        return new While(cond, body);
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

Expression *Parser::parseLit()
{
    std::string token = safePop();
    if (isNumber(token))
    {
        return new Literal(std::atoi(token.c_str()));
    }
    else
    {
        return new Variable(token);
    }
}
