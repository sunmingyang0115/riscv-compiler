#ifndef BRACKETUTIL_H
#define BRACKETUTIL_H
#include <string>

extern std::string OPEN_BRACKETS[];
extern std::string CLOSE_BRACKETS[];
bool isOpenBracket(std::string s);
bool isCloseBracket(std::string s);
bool isMatchingBracketPairs(std::string open, std::string close);
bool isOpenBracket(char c);
bool isCloseBracket(char c);

#endif