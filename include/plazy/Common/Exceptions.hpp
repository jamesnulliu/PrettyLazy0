#pragma once
#include <exception>
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

    virtual const char* what() const noexcept override
    {
        return m_msg.c_str();
    }
};

class UnknownWord : public Exception
{
public:
    UnknownWord(const std::string& word)
    {
        m_msg = "Unknown word: " + word;
    }

    virtual const char* what() const noexcept override
    {
        return m_msg.c_str();
    }
};

class InvalidIdent : public Exception
{
public:
    InvalidIdent(const std::string& ident)
    {
        m_msg = "Invalid identifier: " + ident;
    }

    virtual const char* what() const noexcept override
    {
        return m_msg.c_str();
    }
};

class InvalidOperator : public Exception
{
public:
    InvalidOperator(const std::string& op)
    {
        m_msg = "Invalid operator: " + op;
    }

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

    virtual const char* what() const noexcept override
    {
        return m_msg.c_str();
    }
};

class RuntimeError : public Exception
{
public:
    RuntimeError(const std::string& msg)
    {
        m_msg = "Runtime error: " + msg;
    }

    virtual const char* what() const noexcept override
    {
        return m_msg.c_str();
    }
};

class SyntaxError : public Exception
{
public:
    SyntaxError(const std::string& msg)
    {
        m_msg = "Syntax error: " + msg;
    }

    virtual const char* what() const noexcept override
    {
        return m_msg.c_str();
    }
};

class SemanticError : public Exception
{
public:
    SemanticError(const std::string& msg)
    {
        m_msg = "Semantic error: " + msg;
    }

    virtual const char* what() const noexcept override
    {
        return m_msg.c_str();
    }
};

}  // namespace plazy
