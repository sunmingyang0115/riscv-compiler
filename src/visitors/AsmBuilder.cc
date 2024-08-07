#include "AsmBuilder.hh"
#include <iostream>

AsmBuilder::AsmBuilder()
    : m_stream{}, m_labelLen{0} {}

AsmBuilder::~AsmBuilder() {}


AsmBuilder &AsmBuilder::operator<<(std::string line)
{
    push(line);
    return *this;
}

void AsmBuilder::push(std::string s)
{
    if (s[s.length() - 1] == ':') // label
    {
        m_stream << s;
        m_labelLen = s.length();
    }
    else
    {
        int seperator = -1;
        std::string cmd = s;
        std::string op = "";
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == ' ')
            {
                seperator = i;
                break;
            }
        }
        if (seperator != -1)
        {
            cmd = s.substr(0, seperator);
            op = s.substr(seperator, s.length() - seperator);
        }
        // std::cout << seperator << "\n";

        // std::cout << cmd << "|" << op << "\n";
        m_stream << std::string(8 - m_labelLen, ' ') << cmd << std::string(8 - cmd.length(), ' ') << op << "\n";
        m_labelLen = 0;
    }
}

std::string AsmBuilder::build()
{
    return m_stream.str();
}