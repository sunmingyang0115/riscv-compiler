#include "BracketUtil.hh"
#include <string>

std::string OPEN_BRACKETS[3] = {"(", "[", "{"};
std::string CLOSE_BRACKETS[3] = {")", "]", "}"};

bool isOpenBracket(std::string s)
{
    for (int i = 0; i < 3; i++)
    {
        if (OPEN_BRACKETS[i] == s)
            return true;
    }
    return false;
}
bool isCloseBracket(std::string s)
{
    for (int i = 0; i < 3; i++)
    {
        if (CLOSE_BRACKETS[i] == s)
            return true;
    }
    return false;
}

bool isOpenBracket(char c)
{
    std::string s{c};
    return isOpenBracket(s);
}
bool isCloseBracket(char c)
{
    std::string s{c};
    return isCloseBracket(s);
}
