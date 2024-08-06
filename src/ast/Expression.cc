#include "Expressions.hh"
#include <stdexcept>

Expression::Expression(std::vector<Expression *> children)
: m_children{children} {}

Expression::Expression() : m_children{nullptr} {};
Expression::~Expression()
{
    for (auto it = m_children.begin(); it != m_children.end(); ++it)
    {
        delete *it;
    }
}
