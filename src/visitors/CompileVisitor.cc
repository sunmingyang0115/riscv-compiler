#include <sstream>
#include <fstream>
#include "Visitor.hh"
#include "CompileVisitor.hh"
#include "../ast/Expressions.hh"
#include <map>

std::string getInstructionString(BinOp::Operator op)
{
    std::string res;
    switch (op)
    {
    case BinOp::Operator::PLUS:
        res = "add";
        break;
    case BinOp::Operator::MINUS:
        res = "sub";
        break;
    case BinOp::Operator::TIMES:
        res = "mul";
        break;
    case BinOp::Operator::DIVIDE:
        res = "div";
        break;
    default:
        res = nullptr;
        break;
    }
    return res;
}

std::string CompileVisitor::mutStack(int n)
{
    m_offset += n;
    return "addi sp, sp, " + std::to_string(n);
}

CompileVisitor::CompileVisitor()
{
    m_stream << "## compiled code; modify at your own risk! ##" << std::endl
             << ".global _start" << std::endl
             << "_start:" << std::endl
             << "addi sp,sp,400" << std::endl
             << "add x1, x0, sp # reg x1 is the starting sp of the function" << std::endl
             << std::endl;
}
void CompileVisitor::finishCompile(std::string filename)
{
    m_stream << "lw t1, 4(sp)" << std::endl
             << "add a0, x0, t1" << std::endl
             << "addi a7, x0, 93" << std::endl
             << "ecall" << std::endl
             << std::endl;

    std::ofstream outfile(filename);
    outfile << m_stream.str() << std::endl;
    outfile.close();
}
CompileVisitor::~CompileVisitor() {}

// visitors

void CompileVisitor::visit(Literal *node)
{
    m_stream << "addi t0, x0, " << node->getValue() << std::endl
             << "sw t0, 0(sp)" << std::endl
             << mutStack(-4) << std::endl
             << std::endl;
}
void CompileVisitor::visit(BinOp *node) {}
void CompileVisitor::visit(Sequence *node) {}
void CompileVisitor::visit(Variable *node)
{
    std::string name = node->getName();
    int pos_offset = m_varlist[name];
    m_stream << "lw t0, " << pos_offset << "(x1)" << std::endl
             << "sw t0, 0(sp)" << std::endl
             << mutStack(-4) << std::endl
             << std::endl;
}
void CompileVisitor::visit(Declare *node)
{
    m_varlist[dynamic_cast<Variable *>(node->getVariable())->getName()] = m_offset;
    m_stream << mutStack(-4) << std::endl // push sp after registering variable
             << std::endl;
}
void CompileVisitor::visit(Set *node) {}
void CompileVisitor::leave(Literal *node) {}
void CompileVisitor::leave(BinOp *node)
{
    std::string instruction = getInstructionString(node->getOp());
    m_stream << "lw t0, 4(sp)" << std::endl
             << "lw t1, 8(sp)" << std::endl
             << instruction << " t0, t1, t0" << std::endl
             << "sw t0, 8(sp)" << std::endl
             << mutStack(4) << std::endl
             << std::endl;
}
void CompileVisitor::leave(Sequence *node) {}
void CompileVisitor::leave(Variable *node) {}
void CompileVisitor::leave(Declare *node) {}
void CompileVisitor::leave(Set *node)
{
    std::string name = dynamic_cast<Variable *>(node->getVariable())->getName();
    int pos_offset = m_varlist[name];
    m_stream << "lw t0, 4(sp)" << std::endl
             << "sw t0, " << pos_offset << "(x1)" << std::endl
             << std::endl;
}
