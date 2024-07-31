#ifndef STRINGVISITOR_HH
#define STRINGVISITOR_HH
#include <sstream>
#include "Visitor.hh"


class StringVisitor : public Visitor
{
private:
    std::stringstream *m_stream{};

public:
    StringVisitor();
    ~StringVisitor();
    std::string getString() const { return m_stream->str(); }
    void visit(Literal *node) override;
    void visit(BinOp *node) override;
    void visit(Sequence *node) override;
    void leave(Literal *node) override;
    void leave(BinOp *node) override;
    void leave(Sequence *node) override;
};

#endif
