#include "Tokenizer.hh"
#include <iostream>
#include <ostream>

Tokenizer::Tokenizer(std::string s)
    : m_queue{}
{
    // not correct will change later
    int prev = 0;
    for (int i = s.length()-1; i >= 0; i--)
    {
        prev++;
        if (i == 0 || s[i-1] == ' ')
        {
            m_queue.push_back(s.substr(i, prev-1));
            prev = 0;
        }
    }
}

std::string Tokenizer::getNext() {
    std::string front = m_queue.back();
    m_queue.pop_back();
    return front;
}

int Tokenizer::hasNext()
{
    return m_queue.size();
}


// std::ostream &operator <<(std::ostream &out, const Tokenizer &v) {
//     out << "balls";
//     return out;
// }
