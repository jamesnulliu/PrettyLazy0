#include <format>

#include <Yutils/Logger.hpp>

#include "plazy/Common/Exceptions.hpp"
#include "plazy/Core/Lexer.hpp"
#include "plazy/Core/Parser.hpp"

namespace plazy
{
void Parser::parseProgram()
{
    if (m_tokens.empty()) {
        throw RuntimeError("No tokens to parse.");
    }
    if (match(TokenType::KEYWORD, "const")) {
        previous();
        constDeclaration();
    }
    if (match(TokenType::KEYWORD, "var")) {
        previous();
        varDeclaration();
    }
    if (match(TokenType::KEYWORD, "begin")) {
        previous();
        block();
    }
    YCRITICAL("Parsing completed.");
}

void Parser::constDeclaration()
{
    consume(TokenType::KEYWORD, "const");
    match(TokenType::IDENTIFIER);
    consume(TokenType::OPERATOR, "=");
    match(TokenType::NUMBER);
    while (match(TokenType::DELIMITER, ",")) {
        match(TokenType::IDENTIFIER);
        consume(TokenType::OPERATOR, "=");
        match(TokenType::NUMBER);
    }
}

void Parser::varDeclaration()
{
    consume(TokenType::KEYWORD, "var");
    match(TokenType::IDENTIFIER);
    while (match(TokenType::DELIMITER, ",")) {
        match(TokenType::IDENTIFIER);
    }
}

void Parser::block()
{
    consume(TokenType::KEYWORD, "begin");
    statement();
    while (match(TokenType::DELIMITER, ";")) {
        statement();
    }
    consume(TokenType::KEYWORD, "end");
}

void Parser::statement()
{
    if (match(TokenType::KEYWORD, "if")) {
        previous();
        ifStatement();
    } else if (match(TokenType::KEYWORD, "while")) {
        previous();
        whileStatement();
    } else if (match(TokenType::IDENTIFIER)) {
        previous();
        assignmentStatement();
    } else {
        throw RuntimeError(std::format("Unexpected token: {} with value: {}",
                                       TokenType2Str(curToken().type), curToken().value));
    }
}

void Parser::ifStatement()
{
    consume(TokenType::KEYWORD, "if");
    condition();
    consume(TokenType::KEYWORD, "then");
    statement();
}

void Parser::whileStatement()
{
    consume(TokenType::KEYWORD, "while");
    condition();
    consume(TokenType::KEYWORD, "do");
    statement();
}

void Parser::assignmentStatement()
{
    match(TokenType::IDENTIFIER);
    consume(TokenType::OPERATOR, ":=");
    expression();
}

void Parser::expression()
{
    if (match(TokenType::OPERATOR, "+") || match(TokenType::OPERATOR, "-")) {
        // Skip unary operators (sign of the number)
    }
    term();
    while (match(TokenType::OPERATOR, "+") || match(TokenType::OPERATOR, "-")) {
        term();
    }
}

void Parser::term()
{
    factor();
    while (match(TokenType::OPERATOR, "*") || match(TokenType::OPERATOR, "/")) {
        factor();
    }
}

void Parser::factor()
{
    if (match(TokenType::DELIMITER, "(")) {
        expression();
        consume(TokenType::DELIMITER, ")");
    } else if (match(TokenType::NUMBER)) {
        // Do nothing
    } else if (match(TokenType::IDENTIFIER)) {
        // Do nothing
    } else {
        throw RuntimeError(std::format("Unexpected token: {} with value: {}",
                                       TokenType2Str(curToken().type), curToken().value));
    }
}

void Parser::condition()
{
    expression();
    if (match(TokenType::OPERATOR, "=", "<", "<=", ">", ">=", "#")) {
        expression();
    } else {
        throw RuntimeError(std::format("Unexpected token: {} with value: {}",
                                       TokenType2Str(curToken().type), curToken().value));
    }
}

Token Parser::consume(TokenType tokenType, const std::string& value)
{
    if (!isAtEnd() && curToken().type == tokenType && curToken().value == value) {
        advance();
        return m_tokens[m_curTokenIdx - 1];
    }
    throw RuntimeError(std::format(
        "Expeted token type: {} with value: {}, but got token type: {} with value: {}",
        TokenType2Str(tokenType), value, TokenType2Str(curToken().type), curToken().value));
}

bool Parser::match(TokenType type, const std::string& value)
{
    if (!isAtEnd() && curToken().type == type && (value.empty() || curToken().value == value)) {
        advance();
        return true;
    }
    return false;
}

}  // namespace plazy
