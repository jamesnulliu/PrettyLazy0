#pragma once
#include <exception>
#include <iostream>
#include <string>

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

class AlreadyExists : public std::exception
{
public:
    AlreadyExists(const std::string& name, const std::string& value) : m_name(name), m_value(value)
    {
    }

private:
    virtual const char* what() const noexcept override
    {
        return (m_name + "already exists: " + m_value).c_str();
    }

private:
    std::string m_name;
    std::string m_value;
};


class InvalidType : public std::exception
{
public:
    InvalidType(const std::string& type) : m_type(type)
    {
    }
private:
    virtual const char* what() const noexcept override
    {
        return ("Invalid type: " + m_type).c_str();
    }
private:
    std::string m_type;
};

}  // namespace plazy
