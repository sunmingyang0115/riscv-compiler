#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H
#include "../visitors/Visitor.hh"
#include <vector>
#include <string>

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
public:
    enum Operator
    {
        PLUS,
        MINUS,
        TIMES,
        DIVIDE
    };

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
    std::vector<Expression *> m_expressions{};

public:
    Sequence(std::vector<Expression *> expressions);
    ~Sequence();
    void accept(Visitor *v) override;
    void reject(Visitor *v) override;
    void visitChildren(Visitor *v) override;
};

struct Variable : public Expression
{
private:
    std::string m_name{};

public:
    Variable(std::string name);
    ~Variable();
    std::string getName();
    void accept(Visitor *v) override;
    void reject(Visitor *v) override;
    void visitChildren(Visitor *v) override;
};

struct Declare : public Expression
{
private:
    std::string m_type{};
    Expression *m_variable{};

public:
    Declare(std::string type, Expression *name);
    ~Declare();
    std::string getType();
    Expression *getVariable();
    void accept(Visitor *v) override;
    void reject(Visitor *v) override;
    void visitChildren(Visitor *v) override;
};

struct Set : public Expression
{
private:
    Expression *m_variable{};
    Expression *m_value{};

public:
    Set(Expression *variable, Expression *value);
    ~Set();
    Expression *getVariable();
    Expression *getValue();
    void accept(Visitor *v) override;
    void reject(Visitor *v) override;
    void visitChildren(Visitor *v) override;
};

#endif
