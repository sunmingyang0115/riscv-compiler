#include <iostream>
#include <memory>
#include "lexer/Parser.hh"
#include <sstream>
#include "ast/Expressions.hh"
// #include "visitors/Visitor.hh"
#include "visitors/StringVisitor.hh"
#include "visitors/CompileVisitor.hh"
#include "lexer/Tokenizer.hh"

int main(int argc, char *argv[])
{
    std::stringstream ss;
    for (int i = 1; i < argc; i++) {
        ss << argv[i] << " ";
    }
    // Tokenizer tk{ss.str()};
    // std::cout << "-\n";
    // while (tk.hasNext())
    // {
    //     std::cout << "`" << tk.getNext() << "`" << std::endl;
    // }
    
    Parser parser{ss.str()};
    Expression* e = parser.build();

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
