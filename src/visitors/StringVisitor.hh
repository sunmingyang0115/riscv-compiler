#ifndef STRINGVISITOR_HH
#define STRINGVISITOR_HH
#include <sstream>
#include "Visitor.hh"

class StringVisitor : public Visitor
{
private:
    std::stringstream m_stream{};

public:
    StringVisitor();
    ~StringVisitor();
    std::string getString() const { return m_stream.str(); }
    void visit(Literal *node) override;
    void visit(BinOp *node) override;
    void visit(Sequence *node) override;
    void visit(Variable *node) override;
    void visit(Declare *node) override;
    void visit(Set *node) override;
    void leave(Literal *node) override;
    void leave(BinOp *node) override;
    void leave(Sequence *node) override;
    void leave(Variable *node) override;
    void leave(Declare *node) override;
    void leave(Set *node) override;
};

#endif
