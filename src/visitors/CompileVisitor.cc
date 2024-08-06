#include <sstream>
#include <fstream>
#include "CompileVisitor.hh"
#include "../ast/Expressions.hh"
std::string getUniqueLabel()
{
    static int n = 0;
    return "L" + std::to_string(n++);
}

std::string opToInstruction(BinOp::Operator op)
{
    std::string b, e;
    switch (op)
    {
    case BinOp::Operator::PLUS:
        return "add t0,t0,t1\n";
    case BinOp::Operator::MINUS:
        return "sub t0,t0,t1\n";
    case BinOp::Operator::TIMES:
        return "mul t0,t0,t1\n";
    case BinOp::Operator::DIVIDE:
        return "div t0,t0,t1\n";
    case BinOp::Operator::EQ:
        b = getUniqueLabel();
        e = getUniqueLabel();
        return "beq t0,t1," + b + "\nadd t0,x0,x0\nj " + e + "\n" + b + ":\naddi t0,x0,1\n" + e + ":\n";
    case BinOp::Operator::LT:
        b = getUniqueLabel();
        e = getUniqueLabel();
        return "slt t0,t0,t1\nbne t0,x0," + b + "\nadd t0,x0,x0\nj " + e + "\n" + b + ":\naddi t0,x0,1\n" + e + ":\n";
    case BinOp::Operator::GT:
        b = getUniqueLabel();
        e = getUniqueLabel();
        return "slt t0,t1,t0\nbne t0,x0," + b + "\nadd t0,x0,x0\nj " + e + "\n" + b + ":\naddi t0,x0,1\n" + e + ":\n";
    case BinOp::Operator::LEQ:
        b = getUniqueLabel();
        e = getUniqueLabel();
        return "slt t0,t1,t0\nbeq t0,x0," + b + "\nadd t0,x0,x0\nj " + e + "\n" + b + ":\naddi t0,x0,1\n" + e + ":\n";
    case BinOp::Operator::GEQ:
        b = getUniqueLabel();
        e = getUniqueLabel();
        return "slt t0,t0,t1\nbeq t0,x0," + b + "\nadd t0,x0,x0\nj " + e + "\n" + b + ":\naddi t0,x0,1\n" + e + ":\n";
    default:
        return nullptr;
    }
}

std::string CompileVisitor::mutStack(int n)
{
    m_offset += n;
    return "addi sp,sp," + std::to_string(n);
}

CompileVisitor::CompileVisitor()
    : m_stream{}
{
    m_stream << "## compiled code; modify at your own risk! ##" << std::endl
             << ".global _start" << std::endl
             << "_start:" << std::endl
             << "addi sp,sp,400" << std::endl
             << "add x1,x0,sp # reg x1 is the starting sp of the function" << std::endl
             << std::endl;
}

CompileVisitor::~CompileVisitor() {};

void CompileVisitor::finishCompile(std::string filename)
{
    m_stream << "lw t1,4(sp)" << std::endl
             << "add a0,x0,t1" << std::endl
             << "addi a7,x0,93" << std::endl
             << "ecall" << std::endl
             << std::endl;

    std::ofstream outfile(filename);
    outfile << m_stream.str() << std::endl;
    outfile.close();
}
void CompileVisitor::visit(Literal *node)
{
    m_stream << "addi t0,x0," << node->getValue() << std::endl
             << "sw t0,0(sp)" << std::endl
             << mutStack(-4) << std::endl
             << std::endl;
}
void CompileVisitor::visit(BinOp *node)
{
    // std::string instruction = ;
    int i = 0;
    for (Expression *expr : node->getChildren())
    {
        expr->accept(this);
        if (i++ != 0)
        {
            m_stream << "lw t0,8(sp)" << std::endl
                     << "lw t1,4(sp)" << std::endl
                     << opToInstruction(node->getOp())
                     << "sw t0,8(sp)" << std::endl
                     << mutStack(4) << std::endl
                     << std::endl;
        }
    }
}

void CompileVisitor::visit(Sequence *node)
{
    for (Expression *expr : node->getChildren())
    {
        expr->accept(this);
    }
}

void CompileVisitor::visit(Variable *node)
{
    std::string name = node->getName();
    m_stream << "lw t0," << m_varlist[name] << "(x1)" << std::endl
             << "sw t0,0(sp)" << std::endl
             << mutStack(-4) << std::endl
             << std::endl;
}

void CompileVisitor::visit(Declare *node)
{
    std::string name = static_cast<Variable *>(node->getChildren().at(0))->getName();
    m_varlist[name] = m_offset;
    m_stream << mutStack(-4) << std::endl
             << std::endl;
}

void CompileVisitor::visit(Set *node)
{
    node->getChildren().at(1)->accept(this);
    std::string name = static_cast<Variable *>(node->getChildren().at(0))->getName();
    m_stream << "lw t0,4(sp)" << std::endl
             << "sw t0," << m_varlist[name] << "(x1)" << std::endl
             << std::endl;
}

void CompileVisitor::visit(While *node)
{
    std::string b = getUniqueLabel();
    std::string e = getUniqueLabel();
    m_stream << b << ":" << std::endl;
    node->getChildren().at(0)->accept(this);
    // if 0 then jmp to e
    m_stream << "lw t0,4(sp)" << std::endl
             << "beqz t0," << e << std::endl;
    node->getChildren().at(1)->accept(this);
    m_stream << "j " << b << std::endl
             << e << ":" << std::endl
             << std::endl;
}