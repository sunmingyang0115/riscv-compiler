#include "Tokenizer.hh"
#include "BracketUtil.hh"
#include <algorithm>
#include <sstream>

std::string inflate(std::string s);
void tokenize(std::vector<std::string> &queue, std::string s);
 
Tokenizer::Tokenizer(std::string s)
    : m_queue{}
{
    // s = "(seq " + s + ")";
    s = inflate(s);
    // std::cout << s;
    tokenize(m_queue, s);
    std::reverse(m_queue.begin(), m_queue.end());
}

std::string Tokenizer::peek()
{
    return m_queue.back();
}

std::string Tokenizer::pop()
{
    std::string front = peek();
    m_queue.pop_back();
    return front;
}

int Tokenizer::hasNext()
{
    return m_queue.size();
}



std::string inflate(std::string s)
{
    std::stringstream ss;
    int prev = 0;
    for (int i = 0; i < s.length(); i++)
    {
        if (isOpenBracket(s[i]) || isCloseBracket(s[i]))
        {
            ss << " " << s[i] << " ";
        }
        else
        {
            ss << s[i];
        }
        prev++;
    }
    return ss.str();
}

void tokenize(std::vector<std::string> &queue, std::string s)
{
    int prevSpace = -1;
    bool lastCharIsSpace = true;
    for (int i = 0; i < s.length(); i++)
    {
        if (isspace(s[i]) && !lastCharIsSpace)
        {
            queue.push_back(s.substr(prevSpace + 1, i - prevSpace - 1));
        }
        if (!isspace(s[i]))
        {
            lastCharIsSpace = false;
        }
        if (isspace(s[i]))
        {
            prevSpace = i;
            lastCharIsSpace = true;
        }
    }
}
