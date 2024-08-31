#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H
#include <string>
#include <vector>

namespace AST {

enum DataType {
    D1,
    D2,
    D4,
    D8
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
    NOT,
    XOR,
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
    BinOp op;
    Bin(BinOp op, Expression *left, Expression *right) : op{op}, left{left}, right{right} {}
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
struct Cond : Expression {
    std::vector<Expression *> conds;
    std::vector<Expression *> thens;
    Cond(std::vector<Expression *> &conds, std::vector<Expression *> &thens) : conds{conds}, thens{thens} {}
    ~Cond();
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
struct RefVar : Expression {
    std::string name;
    RefVar(std::string name) : name{name} {}
};
struct RefFun : Expression {
    std::string name;
    std::vector<Expression *> arguments;
    RefFun(std::string name, std::vector<Expression *> arguments) : name{name}, arguments{arguments} {}
    ~RefFun();
};
struct AddrOf : Expression {
    Expression *data;
    AddrOf(Expression *data) : data{data} {}
    ~AddrOf() { delete data; }
};
struct DeRef : Expression {
    Expression *data;
    DataType refTo;
    DeRef(DataType refTo, Expression *data) : refTo{refTo},data{data} {}
    ~DeRef() { delete data; }
};
// struct Namespace : Expression {
//     std::string name;
//     Expression *body;
//     Namespace(std::string name, Expression *body) : name{name}, body{body} {};
//     ~Namespace() { delete body; }
// };
struct Export : Expression {
    std::vector<std::string> datas;
    Export(std::vector<std::string> datas) : datas{datas} {}
    ~Export() {}
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