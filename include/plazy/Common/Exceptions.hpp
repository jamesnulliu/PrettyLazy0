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
        // std::cerr << "Cannot read file: " << file_name << std::endl;
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

class UnknownOperator : std::exception
{
public:
    UnknownOperator(const std::string& op) : m_op(op)
    {
    }

private:
    virtual const char* what() const noexcept override 
    {
        return ("Unknown operator: " + m_op).c_str();
    }

private:
    std::string m_op;
};

class UnknownDelimiter : public std::exception
{
public:
    UnknownDelimiter(const std::string& delim) : m_delim(delim)
    {
    }

    virtual const char* what() const noexcept override 
    {
        return ("Unknown delimiter: " + m_delim).c_str();
    }

private:
    std::string m_delim;
};

class UnknownWord : public std::exception
{
public:
    UnknownWord(const std::string& word) : m_word(word)
    {
    }

private:
    virtual const char* what() const noexcept override 
    {
        return ("Unknown word: " + m_word).c_str();
    }

private:
    std::string m_word;
};

class SizeMismatch : public std::exception
{
public:
    SizeMismatch(const std::string& msg) : m_msg(msg)
    {
    }

private:
    virtual const char* what() const noexcept override 
    {
        return ("Size mismatch: " + m_msg).c_str();
    }

private:
    std::string m_msg;
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