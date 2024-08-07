#ifndef ASMBUILDER_H
#define ASMBUILDER_H
#include <string>
#include <sstream>

class AsmBuilder
{
private:
    std::stringstream m_stream{};
    int m_labelLen{};
    // std::string spaces(int n);

public:
    AsmBuilder();
    ~AsmBuilder();
    void push(std::string label);
    std::string build();
    AsmBuilder &operator<<(std::string line);
};

#endif