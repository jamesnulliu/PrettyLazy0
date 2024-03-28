#pragma once
#include <format>
#include <fstream>
#include <vector>

#include "plazy.hpp"

int main()
{
        // This class is responsible for parsing command-line arguments
        plazy::ArgParser argParser;
        // This line specifies the location of the file to be processed
        argParser.addOption("f", "The source file to be compiled", "string",
                            "data/exp01-recognize-identifier/case01.pl0");
        // This line specifies the location of the file to be output
        argParser.addOption("o", "The output file", "string", "bin/LexerExample.out");
        std::string srcFile, outputFile;
        // Check if the input and output files have been added to argParser
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
        // Before the end of the file is reached in the Lexer, one Token is fetched in turn
        // There are only six types of plazy::Token::type (ENDOFFILE,KEYWORD,OPERATOR,DELIMITER,IDENTIFIER,NUMBER)
        // Where ENDOFFILE indicates that the Lexet file is at the end of the file, the fileIsOpen function returns false
        // Here a Token is taken out, and the file pointer in the Lexer moves by the same length as the Token's value
        // such as the keyword "begin" is 5 characters long, the file pointer moves by 5 characters
        // This means you need to call lexer.nextToken() for every Token you pull out
        // The Token looks something like {plazy::TokenType::KEYWORD,"begin"}
        // Here are some examples of other types 
        // {plazy::TokenType::OPERATOR,"+"}
        // {plazy::TokenType::DELIMITER,","}
        // {plazy::TokenType::IDENTIFIER,"ab"}
        // {plazy::TokenType::NUMBER,"123"}
        // {plazy::TokenType::ENDOFFILE,""}
        while (lexer.fileIsOpen()) {
            // Find out all keywords
            // The lexer.nextToken() takes a Token from the file stored in lexer
            plazy::Token token = lexer.nextToken();
            if (token.type == plazy::TokenType::KEYWORD) {
                // Find the keyword in the keywords vector
                // The std::ranges::find_if algorithm to find the first element in a range (in this case is keywords) that satisfies a certain condition. 
                // This condition is given by a lambda expression that takes a pair as an argument and checks whether pair.first is equal to token.value.
                // If the condition is true, then it points to the element that satisfies the condition; 
                // Otherwise, it points to the element at the end of the range.
                auto it = std::ranges::find_if(
                    keywords, [&token](const auto& pair) { return pair.first == token.value; });

                // If the keyword is not in the vector, add it
                if (it == keywords.end()) {
                    keywords.push_back({token.value, 1});
                } else {
                    // If the keyword is already in the vector, increment its count
                    it->second++;
                }
            }
            // If you want to search for a different type of element, just replace keywords
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
            else
            {
                if(token.type != plazy::TokenType::ENDOFFILE)
                {
                    PLAZY_ERROR("Here the token.type must be of plazy::TokenType::ENDOFFILE");
                }
            }
        }

        std::ofstream output(outputFile,std::ios::trunc);
        if (!output.is_open()) {
            throw plazy::FileOpenFailed(outputFile);
        }

        output << "Keywords:\n";
        // Iterate through the keywords map and print out each keyword and its corresponding value
        for (const auto& pair : keywords) {
            // Use std::format to format the output string with the keyword and its value
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
        /*
            After you call LexerExample(), the output will be in /bin/LexerExample.out
            The output will look like this:
                Keywords:
                (var : 1)
                (begin : 1)
                (read : 1)
                (if : 1)
                (then : 1)
                (write : 2)
                (end : 1)
                Operators:
                (:= : 2)
                (- : 1)
                (> : 1)
                Delimiters:
                (, : 2)
                (; : 5)
                (( : 3)
                () : 3)
                (. : 1)
                Numbers:
                (10 : 1)
                (5 : 1)
                (3 : 1)
                identifiers:
                (x : 3)
                (y : 3)
                (z : 3)
                (else : 1)
        */
}
