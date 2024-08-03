#include "Tokenizer.hh"
#include <algorithm>
#include <sstream>

// Tokenizer::Tokenizer() : m_queue{}{};

Tokenizer::Tokenizer(std::string s)
    : m_queue{}
{
    std::stringstream ss;
    int prev = 0;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '(' || s[i] == ')')
        {
            ss << " " << s[i] << " ";
        }
        else
        {
            ss << s[i];
        }
        prev++;
    }
    s = ss.str();
    int prevSpace = -1;
    bool lastCharIsSpace = true;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == ' ' && !lastCharIsSpace)
        {
            m_queue.push_back(s.substr(prevSpace + 1, i - prevSpace - 1));
        }
        if (s[i] != ' ')
        {
            lastCharIsSpace = false;
        }
        if (s[i] == ' ')
        {
            prevSpace = i;
            lastCharIsSpace = true;
        }
    }
    std::reverse(m_queue.begin(), m_queue.end());
}

std::string Tokenizer::getNext()
{
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
