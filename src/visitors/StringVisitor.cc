
#include <sstream>
#include "Visitor.hh"
#include "StringVisitor.hh"
#include "../ast/Expressions.hh"

std::string getOperatorString(BinOp::Operator op) {
    std::string res;
    switch (op)
    {
    case BinOp::Operator::PLUS:
        res = "+";
        break;
    case BinOp::Operator::MINUS:
        res = "-";
        break;
    case BinOp::Operator::TIMES:
        res = "*";
        break;
    case BinOp::Operator::DIVIDE:
        res = "/";
        break;
    default:
        res = nullptr;
        break;
    }
    return res;
}

StringVisitor::StringVisitor()
    : m_stream{new std::stringstream()}
{
}
StringVisitor::~StringVisitor()
{
    delete m_stream;
}
void StringVisitor::visit(Literal *node) 
{
    *m_stream << node->getValue();
}
void StringVisitor::visit(BinOp *node) 
{
    std::string op = getOperatorString(node->getOp());
    *m_stream << "(" << op << " ";
}
void StringVisitor::leave(Literal *node)
{
    *m_stream << " ";
}
void StringVisitor::leave(BinOp *node) 
{
    *m_stream << ") ";
}

