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

struct Variable : public Expression
{
private:
    std::string m_name{};

public:
    Variable(std::string name);
    ~Variable();
    std::string getName() const { return m_name; };
    void accept(Visitor *v) override;
};

struct Declare : public Expression
{
private:
    std::string m_type{};

public:
    Declare(std::string type, Expression *var);
    ~Declare();
    std::string getType() const { return m_type; }
    void accept(Visitor *v) override;
};

struct Set : public Expression
{
public:
    Set(Expression *variable, Expression *value);
    ~Set();
    void accept(Visitor *v) override;
};

struct While : public Expression
{
public:
    While(Expression* condition, Expression* body);
    ~While();
    void accept(Visitor *v) override;
};

struct If : public Expression
{
public:
    If(Expression* cond, Expression* ifthen, Expression* ifelse);
    ~If();
    void accept(Visitor *v) override;
};

struct Void : public Expression
{
public:
    Void();
    ~Void();
    void accept(Visitor *v) override;
};

struct Function : public Expression
{
private:
    std::string m_name;
    std::string m_retType; 
public:
    Function(std::string name, std::string retType, Expression* args, Expression* body);
    std::string getName() const { return m_name; }
    std::string getRetType() const {return m_retType; }
    ~Function();
    void accept(Visitor *v) override;
};

#endif
