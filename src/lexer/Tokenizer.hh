#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <vector>
#include <string>
#include <iostream>

class Tokenizer
{
private:
    std::vector<std::string> m_queue;

public:
    Tokenizer(std::string s);
    std::vector<std::string> getVector() const { return m_queue; }
    int hasNext();
    std::string peek();
    std::string pop();
};

#endif