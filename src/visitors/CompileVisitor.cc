#include <sstream>
#include <fstream>
#include "CompileVisitor.hh"
#include "../ast/Expressions.hh"
std::string getUniqueLabel()
{
    static int n = 0;
    return "L" + std::to_string(n++);
}

void CompileVisitor::opToInstruction(BinOp::Operator op)
{
    std::string b,  e;
    switch (op)
    {
    case BinOp::Operator::PLUS:
        m_build << "add t0, t0, t1";
        break;
    case BinOp::Operator::MINUS:
        m_build << "sub t0, t0, t1";
        break;
    case BinOp::Operator::TIMES:
        m_build << "mul t0, t0, t1";
        break;
    case BinOp::Operator::DIVIDE:
        m_build << "div t0, t0, t1";
        break;
    case BinOp::Operator::EQ:
        b = getUniqueLabel();
        e = getUniqueLabel();
        m_build << "beq t0, t1, " + b
                << "add t0, x0, x0"
                << "j " + e
                << b + ":"
                << "addi t0, x0, 1"
                << e + ":";
        break;
    case BinOp::Operator::LT:
        b = getUniqueLabel();
        e = getUniqueLabel();
        m_build << "slt t0, t0, t1"
                << "bne t0, x0, " + b
                << "add t0, x0, x0"
                << "j " + e
                << b + ":"
                << "addi t0, x0, 1"
                << e + ":";
        break;
    case BinOp::Operator::GT:
        b = getUniqueLabel();
        e = getUniqueLabel();
        m_build << "slt t0, t1, t0"
                << "bne t0, x0, " + b
                << "add t0, x0, x0"
                << "j " + e
                << b + ":"
                << "addi t0, x0, 1"
                << e + ":";
            break;
    case BinOp::Operator::LEQ:
        b = getUniqueLabel();
        e = getUniqueLabel();
        m_build << "slt t0, t1, t0"
                << "beq t0, x0, " + b
                << "add t0, x0, x0"
                << "j " + e
                << b + ":"
                << "addi t0, x0, 1"
                << e + ":";
                break;
    case BinOp::Operator::GEQ:
        b = getUniqueLabel();
        e = getUniqueLabel();
        m_build << "slt t0, t0, t1"
                << "beq t0, x0, " + b
                << "add t0, x0, x0"
                << "j " + e
                << b + ":"
                << "addi t0, x0, 1"
                << e + ":";
                break;
    }
}

std::string CompileVisitor::mutStack(int n)
{
    m_offset += n;
    return "addi sp, sp, " + std::to_string(n);
}

CompileVisitor::CompileVisitor()
{
    m_build << ".global _start"
            << "_start:"
            << "addi sp, sp, 400"
            << "add x1, x0, sp # reg x1 is the starting sp of the function";
}

CompileVisitor::~CompileVisitor() {};

void CompileVisitor::finishCompile(std::string filename)
{
    m_build << "lw t1, 4(sp)"
            << "add a0, x0, t1"
            << "addi a7, x0, 93"
            << "ecall";

    std::ofstream outfile(filename);
    outfile << m_build.build() << std::endl;
    outfile.close();
}
void CompileVisitor::visit(Literal *node)
{
    m_build << "addi t0, x0, " + std::to_string(node->getValue())
            << "sw t0, 0(sp)"
            << mutStack(-4);
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
            m_build << "lw t0, 8(sp)"
                    << "lw t1, 4(sp)";
            opToInstruction(node->getOp());
            m_build << "sw t0, 8(sp)"
                    << mutStack(4);
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
    m_build << ("lw t0, " + std::to_string(m_varlist[name])) + "(x1)"
            << "sw t0, 0(sp)"
            << mutStack(-4);
}

void CompileVisitor::visit(Declare *node)
{
    std::string name = static_cast<Variable *>(node->getChildren().at(0))->getName();
    m_varlist[name] = m_offset;
    m_build << mutStack(-4);
}

void CompileVisitor::visit(Set *node)
{
    node->getChildren().at(1)->accept(this);
    std::string name = static_cast<Variable *>(node->getChildren().at(0))->getName();
    m_build << "lw t0, 4(sp)"
            << "sw t0, " + std::to_string(m_varlist[name]) + "(x1)";
}

void CompileVisitor::visit(While *node)
{
    std::string b = getUniqueLabel();
    std::string e = getUniqueLabel();
    m_build << b + ":";
    node->getChildren().at(0)->accept(this);
    // if 0 then jmp to e
    m_build << "lw t0, 4(sp)"
            << "beqz t0, " + e;
    node->getChildren().at(1)->accept(this);
    m_build << "j " + b
            << e + ":";
}

void CompileVisitor::visit(If *node)
{
    std::string begin_else = getUniqueLabel();
    std::string end = getUniqueLabel();
    node->getChildren().at(0)->accept(this);
    m_build << "lw t0, 4(sp)"
            << "beqz t0, " + begin_else;
    node->getChildren().at(1)->accept(this);
    m_build << "j " + end
            << begin_else + ":";
    node->getChildren().at(2)->accept(this);
    m_build << end + ":";
}
