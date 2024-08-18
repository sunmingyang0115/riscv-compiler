#ifndef LEXER_H
#define LEXER_H
#include <string>

class Lexer {
private:
    std::string str;
    void filterComment();

public:
    Lexer(std::string str);
    std::string parse();
    ~Lexer();
};

#endif