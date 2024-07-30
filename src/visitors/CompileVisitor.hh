#ifndef COMPILEVISITOR_H
#define COMPILEVISITOR_H
#include <sstream>
#include "Visitor.hh"
// #include "../ast/Expressions.hh"


class CompileVisitor : public Visitor
{
private:
    std::stringstream *m_stream{};

public:
    CompileVisitor();
    ~CompileVisitor();
    void finishCompile(std::string filename);   // will deconstruct class
    void visit(Literal *node) override;
    void visit(BinOp *node) override;
    void leave(Literal *node) override;
    void leave(BinOp *node) override;
};

#endif
