#include "plazy/Core/Lexer.hpp"
#include "plazy/Common/Exceptions.hpp"

#include "plazy.hpp"

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

    if (cIsDelimiter(m_curChar)) {
        return parseDelimiter();
    } else if (cIsOperator(m_curChar)) {
        return parseOperator();
    } else if (cIsDigit(m_curChar)) {
        return parseNumber();
    } else if (cIsAlpha(m_curChar)) {
        return parseKeywordOrIdentifier();
    } else if (m_curChar == PLAZY_EOF) {
        return {TokenType::ENDOFFILE, ""};
    } else if (m_curChar == '"') {
        throw NotImplemented("String parsing is not implemented yet");
    } else {
        return parseUnknownSymbol();
    }
}

void Lexer::nextChar()
{
    if (m_curChar == '\n' || m_curChar == '\r') {
        ++m_curLine;
        m_curCol = 1;
    } else {
        ++m_curCol;
    }
    m_curChar = m_file.get();
}

void Lexer::skipWhitespace()
{
    while (std::isspace(m_curChar)) {
        nextChar();
    }
}

void Lexer::skipComment()
{
    if (m_curChar == '{') {
        do {
            nextChar();
        } while (m_curChar != '}' && m_curChar != PLAZY_EOF);

        if (m_curChar == '}') {
            nextChar();
        }
    }
    skipWhitespace();
}

Token Lexer::parseNumber()
{
    size_t startCol = m_curCol;
    std::string number;
    do {
        number += m_curChar;
        nextChar();
    } while (cIsDigit(m_curChar));

    Token token{TokenType::NUMBER, number};

    if (cIsAlpha(m_curChar)) {
        token.type = TokenType::NONE;
        do {
            token.value += m_curChar;
            nextChar();
        } while (cIsAlphaDigit(m_curChar));
        YERROR("[L{},C{}] Invalid identifier: {}", m_curLine, startCol, token.value);
    }

    return token;
}

Token Lexer::parseDelimiter()
{
    std::string delimiter = std::string(1, m_curChar);
    Token token = {TokenType::DELIMITER, delimiter, m_curLine, m_curCol};
    nextChar();
    return token;
}

Token Lexer::parseOperator()
{
    size_t startCol = m_curCol;
    Token token{TokenType::OPERATOR, std::string(1, m_curChar), m_curLine, m_curCol};
    nextChar();
    if (token.value == "<" || token.value == ">") {
        if (m_curChar == '=') {  // >=, <=
            token.value += '=';
            nextChar();
        }
    } else if (token.value == ":") {
        if (m_curChar == '=') {  // :=
            token.value += '=';
            nextChar();
        } else {
            YERROR("[L{},C{}] Invalid operator: {}", m_curLine, startCol, token.value[0]);
            token.type = TokenType::NONE;
        }
    }
    return token;
}

Token Lexer::parseKeywordOrIdentifier()
{
    std::string word;
    do {
        word += std::tolower(m_curChar);
        nextChar();
    } while (cIsAlphaDigit(m_curChar));
    if (std::ranges::find(KEWORDS_STR, word) != KEWORDS_STR.end()) {
        return {TokenType::KEYWORD, word, m_curLine, m_curCol};
    } else {
        return {TokenType::IDENTIFIER, word, m_curLine, m_curCol};
    }
}

Token Lexer::parseUnknownSymbol()
{
    YERROR("[L{},C{}] Unknown symbol: {}", m_curLine, m_curCol, m_curChar);
    Token token{TokenType::NONE, std::string(1, m_curChar), m_curLine, m_curCol};
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
            YERROR("Unknown operator: {}", token.value);
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
            YERROR("Unknown delimiter: {}", token.value);
        }
    }
    }
    return "nul";
}
}  // namespace plazy