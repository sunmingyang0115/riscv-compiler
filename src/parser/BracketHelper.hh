#ifndef BRACKET_HELPER_H
#define BRACKET_HELPER_H
#include <string>
class BracketHelper {
public:
    static bool isOpenBracket(std::string &s);
    static bool isCloseBracket(std::string &s);
    static bool isOpenBracket(char c);
    static bool isCloseBracket(char c);
    // static bool doBracketsMatch(std::string &s1, std::string &s2);

};

#endif