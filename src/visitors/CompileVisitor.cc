
#include <sstream>
#include <fstream>
#include "Visitor.hh"
#include "CompileVisitor.hh"
#include "../ast/Expressions.hh"

std::string getInstructionString(BinOp::Operator op) {
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

CompileVisitor::CompileVisitor()
    : m_stream{new std::stringstream()}
{
    *m_stream << "## compiled code; modify at your own risk! ##" << std::endl
              << ".global _start" << std::endl
              << "_start:" << std::endl
              << std::endl;
}
void CompileVisitor::finishCompile(std::string filename)
{
    *m_stream << "lw t1, 0(sp)" << std::endl
              << "add a0, x0, t1" << std::endl
              << "addi a7, x0, 93" << std::endl
              << "ecall" << std::endl
              << std::endl;

    std::ofstream outfile(filename);
    outfile << m_stream->str() << std::endl;
    outfile.close();
    // delete this;
}
CompileVisitor::~CompileVisitor()
{
    delete m_stream;
}
void CompileVisitor::visit(Literal *node)
{
    *m_stream << "addi t0, x0, " << node->getValue() << std::endl
              << "sw t0, -4(sp)" << std::endl
              << "addi sp, sp, -4" << std::endl
              << std::endl;
}
void CompileVisitor::visit(BinOp *node)
{
}
void CompileVisitor::leave(Literal *node)
{
}
void CompileVisitor::leave(BinOp *node)
{
    std::string instruction = getInstructionString(node->getOp());
    *m_stream << "lw t0, 0(sp)" << std::endl
              << "lw t1, 4(sp)" << std::endl
              << instruction << " t0, t0, t1" << std::endl
              << "sw t0, 4(sp)" << std::endl
              << "addi sp, sp, 4" << std::endl
              << std::endl;
}
