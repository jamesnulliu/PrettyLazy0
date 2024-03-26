#include "plazy/Core/Lexer.hpp"
#include "plazy/Common/Exceptions.hpp"
#include "plazy/Common/Logger.hpp"

#include <algorithm>
#include <regex>

namespace plazy
{
Lexer::Lexer(const std::string& fileName)
{
    m_file.open(fileName);
    if (!m_file.is_open()) {
        throw FileOpenFailed(fileName);
    }
    nextChar();
}

Lexer::~Lexer()
{
    m_file.close();
}

Token Lexer::nextToken()
{
    skipWhitespace();
    skipComment();

    if (cIsDelimiter(m_currentChar)) {
        return parseDelimiter();
    } else if (cIsOperator(m_currentChar)) {
        return parseOpertor();
    } else if (cIsDigit(m_currentChar)) {
        return parseNumber();
    } else if (cIsAlpha(m_currentChar)) {
        return parseKeywordOrIdentifier();
    } else if (m_currentChar == PLAZY_EOF) {
        return {TokenType::ENDOFFILE, ""};
    } else if (m_currentChar == '"') {
        throw NotImplemented("String parsing is not implemented yet");
    } else {
        std::string str = std::string(1, m_currentChar);
        do{
            nextChar();
            if (m_currentChar == PLAZY_EOF) {
                break;
            }
            str += m_currentChar;
        } while (cIsAlphaDigit(m_currentChar));
        return {TokenType::NONE, str};
    }
}

void Lexer::nextChar()
{
    if (m_currentChar == '\n') {
        ++m_line;
        m_column = 0;
    } else {
        ++m_column;
    }
    m_currentChar = m_file.get();
}

void Lexer::skipWhitespace()
{
    while (std::isspace(m_currentChar)) {
        nextChar();
    }
}

void Lexer::skipComment()
{
    if (m_currentChar == '{') {
        do {
            nextChar();
        } while (m_currentChar != '}' && m_currentChar != PLAZY_EOF);

        if (m_currentChar == '}') {
            nextChar();
        }
    }
    skipWhitespace();
}

Token Lexer::parseNumber()
{
    std::string number;
    do {
        number += m_currentChar;
        nextChar();
    } while (std::isdigit(m_currentChar));

    Token token{TokenType::NUMBER, number};

    if (cIsAlpha(m_currentChar)) {
        token.type = TokenType::NONE;
        token.value += m_currentChar;
        nextChar();
        while (cIsAlphaDigit(m_currentChar)) {
            token.value += m_currentChar;
            nextChar();
        }
        PLAZY_ERROR("[Ln{}, Col{}] Invalid number: {}", m_line, m_column, token.value);
    }

    return token;
}

Token Lexer::parseDelimiter()
{
    Token token = {TokenType::DELIMITER, std::string(1, m_currentChar)};
    nextChar();
    return token;
}

Token Lexer::parseOpertor()
{
    std::string op;
    do {
        op += m_currentChar;
        nextChar();
    } while (cIsOperator(m_currentChar));
    Token token = {{}, op};
    if (std::ranges::find(OPERATORS_STR, op) == OPERATORS_STR.end()) {
        PLAZY_ERROR("[Ln{}, Col{}] Unknown operator: {}", m_line, m_column, op);
        token.type = TokenType::NONE;
    } else {
        token.type = TokenType::OPERATOR;
    }
    return token;
}

Token Lexer::parseKeywordOrIdentifier()
{
    std::string word;
    do {
        word += std::tolower(m_currentChar);
        nextChar();
    } while (cIsAlphaDigit(m_currentChar));
    if (std::ranges::find(KEWORDS_STR, word) != KEWORDS_STR.end()) {
        return {TokenType::KEYWORD, word};
    } else {
        return {TokenType::IDENTIFIER, word};
    }
}
}  // namespace plazy