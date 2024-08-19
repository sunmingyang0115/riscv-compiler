#ifndef BRACKET_HELPER_H
#define BRACKET_HELPER_H
#include <string>
class BracketHelper {
public:
    static bool isOpenBracket(std::string &s);
    static bool isCloseBracket(std::string &s);
    static bool isOpenBracket(char c);
    static bool isCloseBracket(char c);
    static bool doBracketsMatch(std::string &open, std::string &close);
    static bool doBracketsMatch(char open, char close);

};

#endif