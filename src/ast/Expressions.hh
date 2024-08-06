#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H
#include "../visitors/Visitor.hh"
#include <vector>
#include <string>

class Expression
{
private:
    std::vector<Expression *> m_children;

public:
    Expression(std::vector<Expression *> children);
    Expression();
    std::vector<Expression *> getChildren() const { return m_children; }
    virtual void accept(Visitor *v) = 0;
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
};
struct BinOp : public Expression
{
public:
    enum Operator
    {
        // arithmetic
        PLUS,
        MINUS,
        TIMES,
        DIVIDE,
        // boolean
        EQ,
        LT,
        GT,
        LEQ,
        GEQ,
        SIZE    // size of BinOp; also used as sential values
    };

private:
    Operator m_op{};

public:
    BinOp(Operator op, std::vector<Expression *> exprs);
    Operator getOp() const { return m_op; };
    ~BinOp();
    void accept(Visitor *v) override;
};

struct Sequence : public Expression
{

public:
    Sequence(std::vector<Expression *> exprs);
    ~Sequence();
    void accept(Visitor *v) override;
};

// struct Variable : public Expression
// {
// private:
//     std::string m_name{};

// public:
//     Variable(std::string name);
//     ~Variable();
//     std::string getName();
//     void accept(Visitor *v) override;
//     void reject(Visitor *v) override;
//     void visitChildren(Visitor *v) override;
// };

// struct Declare : public Expression
// {
// private:
//     std::string m_type{};
//     Expression *m_variable{};

// public:
//     Declare(std::string type, Expression *name);
//     ~Declare();
//     std::string getType();
//     Expression *getVariable();
//     void accept(Visitor *v) override;
//     void reject(Visitor *v) override;
//     void visitChildren(Visitor *v) override;
// };

// struct Set : public Expression
// {
// private:
//     Expression *m_variable{};
//     Expression *m_value{};

// public:
//     Set(Expression *variable, Expression *value);
//     ~Set();
//     Expression *getVariable();
//     Expression *getValue();
//     void accept(Visitor *v) override;
//     void reject(Visitor *v) override;
//     void visitChildren(Visitor *v) override;
// };

// struct While : public Expression
// {
// private:
//     Expression* m_condition{};
//     Expression* m_body{};

// public:
//     While(Expression* condition, Expression* body);
//     ~While();
//     Expression *getCondition();
//     Expression *getBody();
//     void accept(Visitor *v) override;
//     void reject(Visitor *v) override;
//     void visitChildren(Visitor *v) override;

// };

#endif
