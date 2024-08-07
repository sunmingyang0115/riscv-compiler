#ifndef VISITOR_H
#define VISITOR_H

struct Literal;
struct BinOp;
struct Sequence;
struct Variable;
struct Set;
struct Declare;
struct While;
struct If;

class Visitor
{
public:
    virtual void visit(Literal *node) = 0;
    virtual void visit(BinOp *node) = 0;
    virtual void visit(Sequence *node) = 0;
    virtual void visit(Variable *node) = 0;
    virtual void visit(Declare *node) = 0;
    virtual void visit(Set *node) = 0;
    virtual void visit(While *node) = 0;
    virtual void visit(If *node) = 0;
    virtual ~Visitor() {};
};

#endif