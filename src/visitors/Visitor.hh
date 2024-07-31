#ifndef VISITOR_H
#define VISITOR_H
// #include "../ast/Expressions.hh"

struct Literal;
struct BinOp;
struct Sequence;

class Visitor
{
public:
    virtual void visit(Literal *node) = 0;
    virtual void visit(BinOp *node) = 0;
    virtual void visit(Sequence *node) = 0;
    virtual void leave(Literal *node) = 0;
    virtual void leave(BinOp *node) = 0;
    virtual void leave(Sequence *node) = 0;
    virtual ~Visitor() {};
};

#endif