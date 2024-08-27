#include "Parser.hh"
#include "BracketHelper.hh"
#include "Tokenizer.hh"
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <unordered_map>

bool stringToDataType(AST::DataType *dt, std::string str) {
    static const std::unordered_map<std::string, AST::DataType> map = {
        {"char", AST::DataType::D1},
        {"short", AST::DataType::D2},
        {"int", AST::DataType::D4},
        {"long", AST::DataType::D8}};
    auto it = map.find(str);
    if (it != map.end()) {
        *dt = it->second;
        return true;
    }
    return false;
}

bool stringToBinOp(AST::BinOp *op, std::string str) {
    static const std::unordered_map<std::string, AST::BinOp> map = {
        {"+", AST::BinOp::ADD},
        {"-", AST::BinOp::SUB},
        {"/", AST::BinOp::DIV},
        {"*", AST::BinOp::MUL},
        {"%", AST::BinOp::MOD},
        {"and", AST::BinOp::AND},
        {"or", AST::BinOp::OR},
        {">", AST::BinOp::GT},
        {"<", AST::BinOp::LT},
        {">=", AST::BinOp::GEQ},
        {"<=", AST::BinOp::LEQ},
        {"=", AST::BinOp::EQ},
        {"!=", AST::BinOp::NEQ},
        {"xor", AST::BinOp::XOR},
        {">>", AST::BinOp::BSR},
        {"<<", AST::BinOp::BSL}};
    auto it = map.find(str);
    if (it != map.end()) {
        *op = it->second;
        return true;
    }
    return false;
}

//========= gpt4o ========
bool isNumber(const std::string &str) {
    if (str.empty()) {
        return false;
    }
    std::size_t i = 0;
    if (str[0] == '-' || str[0] == '+') { // Handle optional sign
        i = 1;
    }
    for (; i < str.size(); ++i) {
        if (!std::isdigit(str[i])) {
            return false;
        }
    }
    return true;
}
//========================

class ParseHelper {
private:
    Tokenizer tk;

    AST::Expression *parseSexp(std::string first) {
        if (first == "char^" || first == "short^" || first == "int^" || first == "long^") {
            first.pop_back();
            AST::DataType dt;
            stringToDataType(&dt, first);
            return new AST::DeRef(dt, parse());
        } else if (first == "@") {
            return new AST::AddrOf(parse());
        } else if (!first.rfind("char^", 0) || !first.rfind("short^", 0) || !first.rfind("int^", 0) || !first.rfind("long^", 0)) {
            AST::DataType dt;
            stringToDataType(&dt, first.substr(0, first.find("^")));
            return new AST::DeRef(dt, parseSexp(first.substr(first.find("^")+1)));
        } else if (first[0] == '@') {
            first.erase(0, 1);
            return new AST::AddrOf(parseSexp(first));
        } else if (BracketHelper::isOpenBracket(first)) {
            std::string second = tk.next();
            AST::Expression *parsed = parseList(second);
            std::string close = tk.next();
            if (!BracketHelper::doBracketsMatch(first, close))
                exit(1);
            return parsed;
        } else {
            return parseAtom(first);
        }
    }

    AST::Expression *parseList(std::string car) {
        AST::DataType dt;
        AST::BinOp op;
        if (car == "export") {
            std::vector<std::string> datas;
            while (!BracketHelper::isCloseBracket(car = tk.peek())) {
                datas.push_back(tk.next());
            }
            return new AST::Export(datas);
        }
        else if (stringToDataType(&dt, car)) {
            if (BracketHelper::isOpenBracket(tk.peek())) { // function
                std::string funOpen = tk.next();
                std::string name = tk.next();
                std::vector<std::string> argNames{};
                std::vector<AST::DataType> argTypes{};
                while (!BracketHelper::isCloseBracket(car = tk.peek())) {
                    std::string argOpen = tk.next();
                    stringToDataType(&dt, tk.next());
                    argNames.push_back(tk.next());
                    argTypes.push_back(dt);
                    std::string argClose = tk.next();
                    if (!BracketHelper::doBracketsMatch(argOpen, argClose)) {
                        exit(1);
                    }
                }
                std::string funClose = tk.next();
                if (!BracketHelper::doBracketsMatch(funOpen, funClose)) {
                    exit(1);
                }
                AST::Expression *body = parseList("do");
                return new AST::DefFun(dt, name, argNames, argTypes, body);
            } else { // variable
                return new AST::DefVar(dt, tk.next());
            }
        } else if (stringToBinOp(&op, car)) {
            AST::Expression* left = parse();
            AST::Expression* right = parse();
            return new AST::Bin(op, left, right);
        }
        else if (car == "do") {
            std::vector<AST::Expression *> exprs{};
            while (!BracketHelper::isCloseBracket(car = tk.peek())) {
                exprs.push_back(parse());
            }
            return new AST::Do{exprs};
        } else if (car == "while") {
            AST::Expression *cond = parse();
            AST::Expression *body = parseList("do");
            return new AST::While(cond, body);
        } else if (car == "cond") {
            std::vector<AST::Expression *> conds;
            std::vector<AST::Expression *> thens;
            while(!BracketHelper::isCloseBracket(car = tk.peek())) {
                tk.next();
                conds.push_back(parse());
                thens.push_back(parseList("do"));
                tk.next();
            }
            return new AST::Cond(conds, thens);
        } else if (car == "not") {
            return new AST::Not(parse());
        } else if (car == "set") {
            AST::Expression *data = parse();
            AST::Expression *value = parse();
            return new AST::Set(data, value);
        } else if (car == "exit") {
            return new AST::Exit(parse());
        } else if (car == "cast") {
            stringToDataType(&dt, tk.next());
            AST::Expression *value = parse();
            return new AST::Cast(dt, value);
        } else {
            std::string name = car;
            std::vector<AST::Expression *> args{};
            while (!BracketHelper::isCloseBracket(car = tk.peek())) {
                args.push_back(parse());
            }
            return new AST::RefFun{name, args};
        }
    }

    AST::Expression *parseAtom(std::string atom) {

        if (isNumber(atom)) {
            return new AST::Literal(atom);
        } else {
            return new AST::RefVar(atom);
        }
    }

public:
    ParseHelper(Tokenizer tk) : tk{tk} {
    }
    AST::Expression *parse() {
        std::string first = tk.next();
        return parseSexp(first);
    }
};

std::string filterComments(std::string &raw) {
    // std::istringstream f(raw);
    std::stringstream ss{};
    // std::string line;
    bool commentLine = false;
    bool commentBody = false;
    for (int i = 0; i < raw.size(); i++) {
        if (i != raw.size()) {
            char c = raw[i];
            char cn = raw[i+1];
            if (c == '#' && cn == '|') {
                commentBody = true;
            } else if (c == '|' && cn == '#') {
                i += 2;
                commentBody = false;
            }
        }
        if (!commentBody) {
            if (raw[i] == ';') {
                commentLine = true;
            }
        }
        if (raw[i] == '\n') {
            commentLine = false;
        }
        if (!commentLine && !commentBody) {
            ss << raw[i];
        }
    }
    return ss.str();
}

AST::Expression *parse(std::string &raw) {
    std::string filtered = filterComments(raw);
    Tokenizer tk{filtered};
    ParseHelper ph{tk};
    return ph.parse();
}