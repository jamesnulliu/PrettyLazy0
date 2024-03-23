#pragma once
#include <iostream>
#include <string>
#include <exception>

namespace plazy
{

class FileOpenFailed : public std::exception
{
public:
    FileOpenFailed(const std::string& fileName) : m_fileName(fileName)
    {
    }

private:
    virtual const char* what() const noexcept override 
    {
        return ("Cannot read file: " + m_fileName).c_str();
    }

private:
    std::string m_fileName;
};

class InvalidWord : public std::exception
{
public:
    InvalidWord(const std::string& word) : m_word(word)
    {
    }

private:
    virtual const char* what() const noexcept override 
    {
        return ("Invalid word: " + m_word).c_str();
    }

private:
    std::string m_word;
};


class NotImplemented : public std::exception
{
public:
    NotImplemented(const std::string& msg) : m_msg(msg)
    {
    }
private:
    virtual const char* what() const noexcept override 
    {
        return ("Not implemented: " + m_msg).c_str();
    }
private:
    std::string m_msg;
};
}  // namespace plazy