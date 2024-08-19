#include "BracketHelper.hh"

bool BracketHelper::isOpenBracket(char c) {
    return c == '(' || c == '[' || c == '{'; 
}
bool BracketHelper::isCloseBracket(char c) {
    return c == ')' || c == ']' || c == '}';
}
bool BracketHelper::isOpenBracket(std::string s) {
    return s.length() > 0 && isOpenBracket(s.at(0));
}
bool BracketHelper::isCloseBracket(std::string s) {
    return s.length() > 0 && isCloseBracket(s.at(0));
}
bool BracketHelper::doBracketsMatch(std::string open, std::string close) {
    return open.length() > 0 && close.length() > 0 && doBracketsMatch(open.at(0), close.at(0));

}
bool BracketHelper::doBracketsMatch(char open, char close) {
    return open == '(' && close == ')'
        || open == '[' && close == ']'
        || open == '{' && close == '}';
}