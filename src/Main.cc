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


    // while(tk.get()->hasNext()) {
    //     std::cout << tk.get()->getNext();
    // }std::cout << std::endl;

    // std::unique_ptr<BinOp> e = std::make_unique<BinOp>(BinOp::Operator::PLUS, new Literal(4), new BinOp(BinOp::Operator::TIMES, new Literal(2), new Literal(4)));
    std::unique_ptr<StringVisitor> s = std::make_unique<StringVisitor>();
    std::unique_ptr<CompileVisitor> comp = std::make_unique<CompileVisitor>();

    // e.get()->visitAll(v.get());
    // std::cout << v.get()->getStream()->str() << std::endl;

    e->visitAll(s.get());
    std::cout << s.get()->getString() << std::endl;

    
    e->visitAll(comp.get());
    comp.get()->finishCompile("out.s");
}
