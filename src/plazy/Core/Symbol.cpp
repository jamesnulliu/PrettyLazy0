#include "plazy/Core/Symbol.hpp"

namespace plazy
{
Symbol translate2Symbol(const Token& token)
{
    if (token.type == TokenType::IDENTIFIER) {
        return "id";
    } else if (token.type == TokenType::NUMBER) {
        return "num";
    } else if (token.type == TokenType::ENDOFFILE) {
        // [WARN] This is correct if and only if the whole program is an arithmetic expression.
        return ENDSYM;
    } else {
        return token.value;
    }
}
} // namespace plazy