#pragma once
#include <exception>
#include <iostream>
#include <string>

namespace plazy
{

class Exception : public std::exception
{
public:
    Exception() = default;
    virtual ~Exception() = default;

protected:
    std::string m_msg;
};

class FileOpenFailed : public Exception
{
public:
    FileOpenFailed(const std::string& fileName)
    {
        m_msg = "Cannot read file: " + fileName;
    }

private:
    virtual const char* what() const noexcept override
    {
        return m_msg.c_str();
    }
};

class InvalidWord : public Exception
{
public:
    InvalidWord(const std::string& word)
    {
        m_msg = "Invalid word: " + word;
    }

private:
    virtual const char* what() const noexcept override
    {
        return m_msg.c_str();
    }
};

class NotImplemented : public Exception
{
public:
    NotImplemented(const std::string& msg)
    {
        m_msg = "Not implemented: " + msg;
    }

private:
    virtual const char* what() const noexcept override
    {
        return m_msg.c_str();
    }
};

class AlreadyExists : public Exception
{
public:
    AlreadyExists(const std::string& name, const std::string& value)
    {
        m_msg = name + " already exists: " + value;
    }

private:
    virtual const char* what() const noexcept override
    {
        return m_msg.c_str();
    }
};

class InvalidType : public Exception
{
public:
    InvalidType(const std::string& type)
    {
        m_msg = "Invalid type: " + type;
    }

private:
    virtual const char* what() const noexcept override
    {
        return m_msg.c_str();
    }
};

}  // namespace plazy
