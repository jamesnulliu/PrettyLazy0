#include "plazy/Core/Token.hpp"
#include "plazy/Common/Exceptions.hpp"

namespace plazy
{
std::string TokenType2Str(TokenType tokenType)
{
    switch (tokenType) {
    case plazy::TokenType::IDENTIFIER: {
        return "IDENTIFIER";
    }
    case plazy::TokenType::NUMBER: {
        return "NUMBER";
    }
    case plazy::TokenType::KEYWORD: {
        return "KEYWORD";
    }
    case plazy::TokenType::OPERATOR: {
        return "OPERATOR";
    }
    case plazy::TokenType::DELIMITER: {
        return "Delimiter";
    }
    }
    throw InvalidType("Invalid token type.");
}

std::string TokenType2Str(Token token)
{
    switch (token.type) {
    case plazy::TokenType::IDENTIFIER: {
        return "IDENTIFIER";
    }
    case plazy::TokenType::NUMBER: {
        return "NUMBER";
    }
    case plazy::TokenType::KEYWORD: {
        return "KEYWORD";
    }
    case plazy::TokenType::OPERATOR: {
        return "OPERATOR";
    }
    case plazy::TokenType::DELIMITER: {
        return "Delimiter";
    }
    }
    throw InvalidType("Invalid token type.");
}
}  // namespace plazy
