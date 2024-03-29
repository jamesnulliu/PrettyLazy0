#include "plazy/Common/Exceptions.hpp"
#include "plazy/Common/Logger.hpp"

#include "plazy/Core/Lexer.hpp"

#include <algorithm>

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
        return parseOperator();
    } else if (cIsDigit(m_currentChar)) {
        return parseNumber();
    } else if (cIsAlpha(m_currentChar)) {
        return parseKeywordOrIdentifier();
    } else if (m_currentChar == PLAZY_EOF) {
        return {TokenType::ENDOFFILE, ""};
    } else if (m_currentChar == '"') {
        throw NotImplemented("String parsing is not implemented yet");
    } else {
        return parseUnknownSymbol();
    }
}

void Lexer::nextChar()
{
    if (m_currentChar == '\n' || m_currentChar == '\r') {
        ++m_line;
        m_column = 1;
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
    size_t startCol = m_column;
    std::string number;
    do {
        number += m_currentChar;
        nextChar();
    } while (cIsDigit(m_currentChar));

    Token token{TokenType::NUMBER, number};

    if (cIsAlpha(m_currentChar)) {
        token.type = TokenType::NONE;
        do {
            token.value += m_currentChar;
            nextChar();
        } while (cIsAlphaDigit(m_currentChar));
        PLAZY_ERROR("[Ln{}, Col{}] Invalid identifier: {}", m_line, startCol, token.value);
    }

    return token;
}

Token Lexer::parseDelimiter()
{
    std::string delimiter = std::string(1, m_currentChar);
    Token token = {TokenType::DELIMITER, delimiter};
    nextChar();
    return token;
}

Token Lexer::parseOperator()
{
    size_t startCol = m_column;
    Token token{TokenType::OPERATOR, std::string(1, m_currentChar)};
    nextChar();
    if (token.value == "<" || token.value == ">") {
        if (m_currentChar == '=') {  // >=, <=
            token.value += '=';
            nextChar();
        }
    } else if (token.value == ":") {
        if (m_currentChar == '=') {  // :=
            token.value += '=';
            nextChar();
        } else {
            PLAZY_ERROR("[Ln{}, Col{}] Invalid operator: {}", m_line, startCol, token.value[0]);
            token.type = TokenType::NONE;
        }
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

Token Lexer::parseUnknownSymbol()
{
    PLAZY_ERROR("[Ln{}, Col{}] Unknown symbol: {}", m_line, m_column, m_currentChar);
    Token token{TokenType::NONE, std::string(1, m_currentChar)};
    nextChar();
    return token;
}

std::string Lexer::getEncodedType(const plazy::Token& token)
{
    switch (token.type) {
    case plazy::TokenType::IDENTIFIER: {
        return "ident";
    }
    case plazy::TokenType::NUMBER: {
        return "number";
    }
    case plazy::TokenType::KEYWORD: {
        return token.value + "sym";
    }
    case plazy::TokenType::OPERATOR: {
        if (token.value == "+") {
            return "plus";
        } else if (token.value == "-") {
            return "minus";
        } else if (token.value == "*") {
            return "times";
        } else if (token.value == "/") {
            return "slash";
        } else if (token.value == "=") {
            return "eql";
        } else if (token.value == "#") {
            return "neq";
        } else if (token.value == "<") {
            return "lss";
        } else if (token.value == "<=") {
            return "leq";
        } else if (token.value == ">") {
            return "gtr";
        } else if (token.value == ">=") {
            return "geq";
        } else if (token.value == ":=") {
            return "becomes";
        } else {
            PLAZY_ERROR("Unknown operator: {}", token.value);
        }
    }
    case plazy::TokenType::DELIMITER: {
        if (token.value == "(") {
            return "lparen";
        } else if (token.value == ")") {
            return "rparen";
        } else if (token.value == ",") {
            return "comma";
        } else if (token.value == ";") {
            return "semicolon";
        } else if (token.value == ".") {
            return "period";
        } else {
            PLAZY_ERROR("Unknown delimiter: {}", token.value);
        }
    }
    }
    return "nul";
}
}  // namespace plazy