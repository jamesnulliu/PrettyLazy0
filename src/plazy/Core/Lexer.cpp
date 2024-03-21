#include "plazy/Core/Lexer.hpp"
#include "plazy/Common/Exceptions.hpp"
#include <algorithm>

plazy::Lexer::Lexer(const std::string& fileName)
{
    m_file.open(fileName);
    if (!m_file.is_open()) {
        throw plazy::FileOpenFailed(fileName);
    }
    nextChar();
}

plazy::Lexer::~Lexer()
{
    m_file.close();
}

plazy::Token plazy::Lexer::nextToken()
{
    skipWhitespace();
    skipComment();

    if (std::isdigit(m_currentChar)) {
        return getNumber();
    } else if (std::ispunct(m_currentChar)) {
        return getOperator();
    } else if (std::isalpha(m_currentChar)) {
        return getKeywordOrIdentifier();
    } else if (m_currentChar == '"') {
        // return parseString();
        throw NotImplemented("String parsing is not implemented yet");
    } else if (m_currentChar == EOF) {
        return {TokenType::ENDOFFILE, ""};
    } else {
        throw InvalidWord(std::string(1, m_currentChar));
    }
}

void plazy::Lexer::nextChar()
{
    m_currentChar = m_file.get();
}

void plazy::Lexer::skipWhitespace()
{
    while (std::isspace(m_currentChar)) {
        nextChar();
    }
}

void plazy::Lexer::skipComment()
{
    if (m_currentChar == '{') {
        while (m_currentChar != '}' && m_currentChar != EOF) {
            nextChar();
        }
        nextChar();
    }
}

plazy::Token plazy::Lexer::getNumber()
{
    std::string number;
    while (std::isdigit(m_currentChar)) {
        number += m_currentChar;
        nextChar();
    }
    return {TokenType::NUMBER, number};
}

plazy::Token plazy::Lexer::getOperator()
{
    std::string op;
    while (std::ispunct(m_currentChar)) {
        op += m_currentChar;
        nextChar();
    }
    if (std::ranges::find(OPERATORS, op) == OPERATORS.end()) {
        throw plazy::UnknownOperator(op);
    }
    return {TokenType::OPERATOR, op};
}

plazy::Token plazy::Lexer::parseDelimiter()
{
    std::string delimiter;
    while (std::ispunct(m_currentChar)) {
        delimiter += m_currentChar;
        nextChar();
    }
    if (std::ranges::find(DELIMITERS, delimiter) == DELIMITERS.end()) {
        throw plazy::UnknownDelimiter(delimiter);
    }
    return {TokenType::DELIMITER, delimiter};
}

plazy::Token plazy::Lexer::getKeywordOrIdentifier()
{
    std::string word;
    while (std::isalnum(m_currentChar)) {
        word += m_currentChar;
        nextChar();
    }

    if (std::ranges::find(KEYWORDS, word) != KEYWORDS.end()) {
        return {TokenType::KEYWORD, word};
    } else {
        return {TokenType::IDENTIFIER, word};
    }
}