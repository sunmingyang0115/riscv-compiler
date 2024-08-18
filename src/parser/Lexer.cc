#include "Lexer.hh"

void Lexer::filterComment() {
    std::string filtered;
    bool lineComment = false;
    bool docComment = false;
    for (int i = 0; i < this->str.length(); i++) {

        if (i - 1 < this->str.length() && this->str.at(i) == '#' && this->str.at(i + 1) == '|') {
            docComment = true;
        } else if (i - 1 < this->str.length() && this->str.at(i) == '|' && this->str.at(i + 1) == '#') {
            docComment = false;
            i+=2;
        } else if (!docComment) {
            if (this->str.at(i) == ';') {
                lineComment = true;
            } else if (this->str.at(i) == '\n') {
                lineComment = false;
            }
        }
        if (!lineComment && !docComment)
            filtered.push_back(this->str.at(i));
    }
    str = filtered;
}

Lexer::Lexer(std::string str) : str{str} {
    filterComment();
}

std::string Lexer::parse() {
    return this->str;
}
