
#include <iostream>
#include <regex>
#include "Tokenizer.hh"
#include <sstream>
#include "BracketHelper.hh"

Tokenizer::Tokenizer(std::string &s) : data{s}, pos{0} {}

Tokenizer::~Tokenizer() {}

int Tokenizer::getNextPosition() {
    while (this->data[this->pos] == ' ' && this->data.length() > this->pos) {
        this->pos++;
    }
    if (this->data.length() <= this->pos) return -1;
    
    char f = this->data[this->pos];
    if (BracketHelper::isOpenBracket(f) || BracketHelper::isCloseBracket(f)) return this->pos+1;
    for (int i = this->pos; i < this->data.length(); i++) {
        if (this->data[i] == ' ') return i;
        else if (BracketHelper::isOpenBracket(this->data[i]) || BracketHelper::isCloseBracket(this->data[i])) return i;
    }
    return -1;
}

std::string Tokenizer::next() {
    int n = getNextPosition();
    std::string res = this->data.substr(this->pos, n-this->pos);
    this->pos = n;
    return res;
}
std::string Tokenizer::peek() {
    int n = getNextPosition();
    std::string res = this->data.substr(this->pos, n - this->pos);
    return res;
}
bool Tokenizer::hasNext() { return getNextPosition() != -1; }

