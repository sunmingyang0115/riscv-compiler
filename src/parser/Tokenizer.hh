#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <string>
#include <vector>
class Tokenizer {
private:
    const std::string &data;
    std::string buffer;
    int pos;
    int getNextPosition();

public:
    Tokenizer(std::string &s);
    ~Tokenizer();
    std::string next();
    std::string peek();
    bool hasNext();
};


#endif