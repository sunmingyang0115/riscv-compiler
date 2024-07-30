#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H
#include "../visitors/Visitor.hh"

// template <typename Derived>
class Expression
{
public:
    virtual void accept(Visitor *v) = 0;
    virtual void leave(Visitor *v) = 0;
    virtual void visitChildren(Visitor *v) = 0;
    void visitAll(Visitor *v);
    virtual ~Expression();
};


struct Literal : public Expression
{
private:
    int m_number{};

public:
    Literal(int number);
    int getValue() const { return m_number; }
    virtual ~Literal();
    void accept(Visitor *v) override;
    void leave(Visitor *v) override;
    void visitChildren(Visitor *v) override;
};

struct BinOp : public Expression
{
public: enum Operator {PLUS, MINUS, TIMES, DIVIDE};

private:
    Operator m_op{};
    Expression *m_left{};
    Expression *m_right{};

public:
    BinOp(Operator op, Expression *left, Expression *right);
    Operator getOp() const { return m_op; };
    virtual ~BinOp();
    void accept(Visitor *v) override;
    void leave(Visitor *v) override;
    void visitChildren(Visitor *v) override;
};


#endif