#include "Parser.hh"
#include "BracketHelper.hh"
#include "Tokenizer.hh"
#include <cstdlib>

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
        if (BracketHelper::isOpenBracket(first)) {
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
        if (car == "do") {
            std::vector<AST::Expression *> exprs{};
            while (!BracketHelper::isCloseBracket(car = tk.peek())) {
                exprs.push_back(parse());
            }
            return new AST::Do{exprs};
        } else if (car == "while") {
            AST::Expression* cond = parse();
            AST::Expression* body = parseList("do");
            return new AST::While(cond, body);
        } else if (car == "if") {
            AST::Expression* cond = parse();
            AST::Expression* ifthen = parse();
            AST::Expression* ifelse = parse();
            return new AST::If(cond, ifthen, ifelse);
        } else if (car == "not") {
            return new AST::Not(parse());
        } else if (car == "set") {
            AST::Expression* data = parse();
            AST::Expression* value = parse();
            return new AST::Set(data, value);
        }
        else {
            exit(-1);
        }
    }

    AST::Expression *parseAtom(std::string atom) {
        // currently all atoms are either identifiers or literal (numbers)
        if (atom[0] == '*') {
            atom.erase(0, 1);
            return new AST::DeRef(parseSexp(atom));
        }
        else if (atom[0] == '&') {
            atom.erase(0, 1);
            return new AST::AddrOf(parseSexp(atom));
        }
        else if (isNumber(atom)) {
            return new AST::Literal(atom);
        } else {
            return new AST::Ref(atom);
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

AST::Expression *parse(std::string &raw) {
    Tokenizer tk{raw};
    ParseHelper ph{tk};
    return ph.parse();
}
