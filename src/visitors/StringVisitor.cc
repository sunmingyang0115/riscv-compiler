#include <sstream>
#include "Visitor.hh"
#include "StringVisitor.hh"
#include "../ast/Expressions.hh"

std::string opToStr(BinOp::Operator op)
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
    case BinOp::Operator::EQ:
        res = "=";
        break;
    case BinOp::Operator::LT:
        res = "<";
        break;
    case BinOp::Operator::GT:
        res = ">";
        break;
    case BinOp::Operator::LEQ:
        res = "<=";
        break;
    case BinOp::Operator::GEQ:
        res = ">=";
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
    std::string op = opToStr(node->getOp());
    m_stream << "(" << op << " ";
    int i = 0;
    for (Expression *expr : node->getChildren())
    {
        expr->accept(this);
        if (++i != node->getChildren().size())
        {
            m_stream << " ";
        }
    }
    m_stream << ")";
}
void StringVisitor::visit(Sequence *node)
{
    int i = 0;
    for (Expression *expr : node->getChildren())
    {
        expr->accept(this);
        if (++i != node->getChildren().size())
        {
            m_stream << " ";
        }
    }
    m_stream << ")";
}
// void StringVisitor::visit(Variable *node)
// {
//     // m_stream << "(var " << node->getName() << " ";
// }
// void StringVisitor::visit(Declare *node)
// {
//     // m_stream << "(int " << dynamic_cast<Variable *>(node->getVariable())->getName() << " ";
// }
// void StringVisitor::visit(Set *node)
// {
//     // m_stream << "(set " << dynamic_cast<Variable *>(node->getVariable())->getName() << " ";
// }
// void StringVisitor::visit(While *node)
// {
//     // m_stream << "(while ";
// }

