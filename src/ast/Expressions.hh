#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H
#include <string>
#include <vector>

namespace AST {

enum DataType {
    d1,
    d2,
    d4,
    d8
};
enum BinOp {
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    AND,
    OR,
    GT,
    LT,
    GEQ,
    LEQ,
    EQ,
    NEQ,
    BSR,
    BSL
};

struct Expression {
    virtual ~Expression() {};
};
struct Literal : Expression {
public:
    std::string value;
    Literal(std::string value) : value{value} {}
};
struct Bin : Expression {
public:
    Expression *left;
    Expression *right;
    Bin(Expression *left, Expression *right) : left{left}, right{right} {}
    ~Bin() { delete left, delete right; }
};
struct Do : Expression {
    std::vector<Expression *> expressions;
    Do(std::vector<Expression *> &expressions) : expressions{expressions} {};
    ~Do();
};
struct While : Expression {
    Expression *cond;
    Expression *body;
    While(Expression *cond, Expression *body) : cond{cond}, body{body} {}
    ~While() { delete cond, delete body; }
};
struct If : Expression {
    Expression *cond;
    Expression *ifThen;
    Expression *ifElse;
    If(Expression *cond, Expression *ifThen, Expression *ifElse) : cond{cond}, ifThen{ifThen}, ifElse{ifElse} {}
    ~If() { delete cond, delete ifThen, delete ifElse; }
};
struct Not : Expression {
    Expression *value;
    Not(Expression *value) : value{value} {}
    ~Not() { delete value; }
};
struct Set : Expression {
    Expression *data;
    Expression *value;
    Set(Expression *data, Expression *value) : data{data}, value{value} {}
    ~Set() { delete data, delete value; }
};
struct DefVar : Expression {
    DataType dataType;
    std::string name;
    DefVar(DataType dataType, std::string name) : dataType{dataType}, name{name} {}
};
struct DefFun : Expression {
    DataType returnType;
    std::string name;
    std::vector<std::string> argNames;
    std::vector<DataType> argTypes;
    Expression *body;
    DefFun(DataType returnType, std::string name, std::vector<std::string> &argNames, std::vector<DataType> &argTypes, Expression *body)
        : returnType{returnType}, name{name}, argNames{argNames}, argTypes{argTypes}, body{body} {}
    ~DefFun() { delete body; }
};
struct Ref : Expression {
    Expression *data;
    Ref(Expression *data) : data{data} {}
    ~Ref() { delete data; }
};
struct AddrOf : Expression {
    Expression *data;
    AddrOf(Expression *data) : data{data} {}
    ~AddrOf() { delete data; }
};
struct DeRef : Expression {
    Expression *data;
    DeRef(Expression *data) : data{data} {}
    ~DeRef() { delete data; }
};
struct Namespace : Expression {
    std::string name;
    Expression *body;
    Namespace(std::string name, Expression *body) : name{name}, body{body} {};
    ~Namespace() { delete body; }
};
struct Exit : Expression {
    Expression *value;
    Exit(Expression *value) : value{value} {}
    ~Exit() { delete value; }
};
struct Cast : Expression {
    DataType conversionTo;
    Expression *data;
    Cast(DataType conversionTo, Expression *data) : conversionTo{conversionTo}, data{data} {}
    ~Cast() { delete data; }
};

} // namespace AST

#endif