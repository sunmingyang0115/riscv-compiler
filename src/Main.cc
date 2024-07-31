#include <iostream>
#include <memory>
#include "lexer/Parser.hh"
#include <sstream>
#include "ast/Expressions.hh"
// #include "visitors/Visitor.hh"
#include "visitors/StringVisitor.hh"
#include "visitors/CompileVisitor.hh"

int main(int argc, char *argv[])
{
    std::unique_ptr<std::stringstream> ss = std::make_unique<std::stringstream>();
    for (int i = 1; i < argc; i++) {
        *ss.get() << argv[i] << " ";
    }
    
    std::unique_ptr<Parser> parser = std::make_unique<Parser>(ss.get()->str());
    Expression* e = parser.get()->build();

    if (e == nullptr) {
        std::cout << "syntax error" << std::endl;
        return 1;
    }

    std::unique_ptr<StringVisitor> s = std::make_unique<StringVisitor>();
    std::unique_ptr<CompileVisitor> comp = std::make_unique<CompileVisitor>();

    e->visitAll(s.get());
    std::cout << s.get()->getString() << std::endl;

    e->visitAll(comp.get());
    comp.get()->finishCompile("out.s");

    delete e;
}
