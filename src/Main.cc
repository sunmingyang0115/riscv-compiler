#include <iostream>
#include <memory>
#include "lexer/Parser.hh"
#include <sstream>
#include "ast/Expressions.hh"
#include <fstream>
#include "visitors/StringVisitor.hh"
#include "visitors/CompileVisitor.hh"
#include "lexer/Tokenizer.hh"
#include "visitors/AsmBuilder.hh"



int main(int argc, char *argv[])
{
    
    std::string path;
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "-f")
        {
            path = argv[++i];
        }
    }
    std::ifstream file{path};
    if (!file.is_open())
    {
        std::cerr << "Failed to open " << path << std::endl;
        return 1;
    }
    std::stringstream ss;
    std::string line;
    while (getline(file, line)) {
        ss << line << std::endl;
    }
    file.close();
    
    Parser parser{ss.str()};
    Expression* e = parser.build();
    // std::vector<Expression *> v;
    // v.push_back(new Literal(5));
    // v.push_back(new Literal(2));
    // Expression *e = new BinOp(BinOp::Operator::DIVIDE, v);

    if (e == nullptr) {
        std::cerr << "syntax error" << std::endl;
        return 1;
    }

    std::unique_ptr<StringVisitor> s = std::make_unique<StringVisitor>();
    e->accept(s.get());
    std::cout << s.get()->getString() << std::endl;

    std::unique_ptr<CompileVisitor> comp = std::make_unique<CompileVisitor>();
    e->accept(comp.get());
    comp.get()->finishCompile("out.s");

    delete e;
}
