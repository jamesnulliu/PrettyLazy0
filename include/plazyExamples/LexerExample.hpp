#pragma once
#include "plazy/Common/ArgParser.hpp"
#include "plazy/Common/Exceptions.hpp"
#include "plazy/Common/Logger.hpp"
#include "plazy/Core/Lexer.hpp"
#include <format>
#include <fstream>
#include <vector>
inline void lexerExample()
{
    try {
        plazy::ArgParser argParser;
        argParser.addOption("f", "The source file to be compiled", "string",
                            "data/exp01-recognize-identifier/case01.pl0");
        argParser.addOption("o", "The output file", "string", "bin/LexerExample.out");
        std::string srcFile, outputFile;
        auto value = argParser.get<std::string>("f");
        if (value) {
            PLAZY_TRACE("Source file: {}", value.value());
            srcFile = value.value();
        } else {
            PLAZY_ERROR("Source file not provided");
        }
        value = argParser.get<std::string>("o");
        if (value) {
            PLAZY_TRACE("Output file: {}", value.value());
            outputFile = value.value();
        } else {
            PLAZY_ERROR("Output file not provided");
        }
        plazy::Lexer lexer(srcFile);
        // Lexer can find all the keywords operators, delimiters, numbers, and maybe a string of identifiers in the statement
        std::vector<std::pair<std::string, size_t>> keywords;
        std::vector<std::pair<std::string, size_t>> operators;
        std::vector<std::pair<std::string, size_t>> delimiters;
        std::vector<std::pair<std::string, size_t>> numbers;
        std::vector<std::pair<std::string, size_t>> identifiers;
        while (lexer.fileIsOpen()) {
            // Find out all keywords
            plazy::Token token = lexer.nextToken();
            if (token.type == plazy::TokenType::KEYWORD) {
                auto it = std::ranges::find_if(
                    keywords, [&token](const auto& pair) { return pair.first == token.value; });

                if (it == keywords.end()) {
                    keywords.push_back({token.value, 1});
                } else {
                    it->second++;
                }
            }
            // Find out all operators
            else if (token.type == plazy::TokenType::OPERATOR) {
                auto it = std::ranges::find_if(
                    operators, [&token](const auto& pair) { return pair.first == token.value; });

                if (it == operators.end()) {
                    operators.push_back({token.value, 1});
                } else {
                    it->second++;
                }
            }
            // Find out all delimiters
            else if (token.type == plazy::TokenType::DELIMITER) {
                auto it = std::ranges::find_if(
                    delimiters, [&token](const auto& pair) { return pair.first == token.value; });

                if (it == delimiters.end()) {
                    delimiters.push_back({token.value, 1});
                } else {
                    it->second++;
                }
            }
            // Find out all numbers
            else if (token.type == plazy::TokenType::NUMBER) {
                auto it = std::ranges::find_if(
                    numbers, [&token](const auto& pair) { return pair.first == token.value; });

                if (it == numbers.end()) {
                    numbers.push_back({token.value, 1});
                } else {
                    it->second++;
                }
            }
            // Find out all identifiers
            else if (token.type == plazy::TokenType::IDENTIFIER) {
                auto it = std::ranges::find_if(
                    identifiers, [&token](const auto& pair) { return pair.first == token.value; });

                if (it == identifiers.end()) {
                    identifiers.push_back({token.value, 1});
                } else {
                    it->second++;
                }
            }
        }

        std::ofstream output(outputFile,std::ios::trunc);
        if (!output.is_open()) {
            throw plazy::FileOpenFailed(outputFile);
        }

        output << "Keywords:\n";
        for (const auto& pair : keywords) {
            output << std::format("({} : {})\n", pair.first, pair.second);
        }
        output << "Operators:\n";
        for (const auto& pair : operators) {
            output << std::format("({} : {})\n", pair.first, pair.second);
        }
        output << "Delimiters:\n";
        for (const auto& pair : delimiters) {
            output << std::format("({} : {})\n", pair.first, pair.second);
        }
        output << "Numbers:\n";
        for (const auto& pair : numbers) {
            output << std::format("({} : {})\n", pair.first, pair.second);
        }
        output << "identifiers:\n";
        for (const auto& pair : identifiers) {
            output << std::format("({} : {})\n", pair.first, pair.second);
        }
        output.close();
    }
    catch (const std::exception& e) {
        PLAZY_ERROR("{}",e.what());
    }
    catch(...)
    {
        PLAZY_ERROR("Unknown error");
    }
}