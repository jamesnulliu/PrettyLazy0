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
        return getOperatorOrDelimiter();
    } else if (std::isalpha(m_currentChar)) {
        return getKeywordOrIdentifier();
    } else if (m_currentChar == PLAZY_EOF) {
        return {TokenType::ENDOFFILE, ""};
    } else if (m_currentChar == '"') {
        // return parseString();
        throw NotImplemented("String parsing is not implemented yet");
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
        do {
            nextChar();
        } while (m_currentChar != '}' && m_currentChar != PLAZY_EOF);

        if (m_currentChar == '}') {
            nextChar();
        }
    }
    skipWhitespace();
}

plazy::Token plazy::Lexer::getNumber()
{
    std::string number;
    do {
        number += m_currentChar;
        nextChar();
    } while (std::isdigit(m_currentChar));

    // If the current char is an alphabet, then it is an invalid word.
    if (std::isalpha(m_currentChar)) {
        throw InvalidWord(number + m_currentChar);
    }
    return {TokenType::NUMBER, number};
}

plazy::Token plazy::Lexer::getOperatorOrDelimiter()
{
    Token token;
    if (std::ranges::find(DELIMITERS, m_currentChar) != DELIMITERS.end()) {
        token = {TokenType::DELIMITER, std::string(1, m_currentChar)};
    } else if (std::ranges::find(SPECIAL_OPERATORS, m_currentChar) != SPECIAL_OPERATORS.end()) {
        std::string op = std::string(1, m_currentChar);
        nextChar();
        if (m_currentChar == '=') {  // <=, >=, :=
            op += m_currentChar;
        } else {
            if (op == ":") {
                throw InvalidWord(op);
            }
        }
        token = {TokenType::OPERATOR, op};
    } else if (std::ranges::find(SINGLE_OPERATORS, m_currentChar) != SINGLE_OPERATORS.end()) {
        token = {TokenType::OPERATOR, std::string(1, m_currentChar)};
    } else {
        throw InvalidWord(std::string(1, m_currentChar));
    }
    nextChar();
    return token;
}

plazy::Token plazy::Lexer::getKeywordOrIdentifier()
{
    std::string word;
    do {
        word += std::tolower(m_currentChar);
        nextChar();
    } while (std::isalnum(m_currentChar));

    if (std::ranges::find(KEYWORDS, word) != KEYWORDS.end()) {
        return {TokenType::KEYWORD, word};
    } else {
        return {TokenType::IDENTIFIER, word};
    }
}