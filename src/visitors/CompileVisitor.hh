#ifndef COMPILEVISITOR_H
#define COMPILEVISITOR_H
#include <map>
#include "../ast/Expressions.hh"
#include "Visitor.hh"
#include "AsmBuilder.hh"

class CompileVisitor : public Visitor
{
private:
    AsmBuilder m_build{};
    std::string mutStack(int n);
    void opToInstruction(BinOp::Operator op);
    int m_offset{0};
    std::map<std::string, int> m_varlist{};

public:
    CompileVisitor();
    ~CompileVisitor();
    void finishCompile(std::string filename); // will deconstruct class
    void visit(Literal *node) override;
    void visit(BinOp *node) override;
    void visit(Sequence *node) override;
    void visit(Variable *node) override;
    void visit(Declare *node) override;
    void visit(Set *node) override;
    void visit(While *node) override;
    void visit(If *node) override;
};

#endif
