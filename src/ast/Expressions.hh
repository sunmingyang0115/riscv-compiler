#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H
#include "../visitors/Visitor.hh"
#include <vector>

class Expression
{
public:
    virtual void accept(Visitor *v) = 0;
    virtual void reject(Visitor *v) = 0;
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
    ~Literal();
    void accept(Visitor *v) override;
    void reject(Visitor *v) override;
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
    ~BinOp();
    void accept(Visitor *v) override;
    void reject(Visitor *v) override;
    void visitChildren(Visitor *v) override;
};

struct Sequence : public Expression
{
private:
    std::vector<Expression*> m_expressions{};

public:
    Sequence(std::vector<Expression*> expressions);
    ~Sequence();
    void accept(Visitor *v) override;
    void reject(Visitor *v) override;
    void visitChildren(Visitor *v) override;
};


// struct Variable : public Expression
// {
// private:
//     std::string m_name{};
    
// public:
//     Sequence(std::string name)
// }

#endif