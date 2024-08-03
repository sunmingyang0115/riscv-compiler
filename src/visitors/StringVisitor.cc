#include <sstream>
#include "Visitor.hh"
#include "StringVisitor.hh"
#include "../ast/Expressions.hh"

std::string getOperatorString(BinOp::Operator op)
{
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
{
}
StringVisitor::~StringVisitor()
{
}
void StringVisitor::visit(Literal *node)
{
    m_stream << node->getValue();
}
void StringVisitor::visit(BinOp *node)
{
    std::string op = getOperatorString(node->getOp());
    m_stream << "(" << op << " ";
}
void StringVisitor::visit(Sequence *node)
{
    m_stream << "(seq ";
}
void StringVisitor::visit(Variable *node)
{
    m_stream << node->getName();
}
void StringVisitor::visit(Declare *node)
{
    m_stream << "(int " << dynamic_cast<Variable *>(node->getVariable())->getName() << " ";
}
void StringVisitor::visit(Set *node)
{
    m_stream << "(set " << dynamic_cast<Variable *>(node->getVariable())->getName() << " ";
}
void StringVisitor::leave(Literal *node)
{
    m_stream << " ";
}
void StringVisitor::leave(BinOp *node)
{
    m_stream << ") ";
}
void StringVisitor::leave(Sequence *node)
{
    m_stream << ") ";
}
void StringVisitor::leave(Variable *node)
{
    m_stream << " ";
}
void StringVisitor::leave(Declare *node)
{
    m_stream << ") ";
}
void StringVisitor::leave(Set *node)
{
    m_stream << ") ";
}
