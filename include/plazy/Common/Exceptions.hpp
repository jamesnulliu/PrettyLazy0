#pragma once
#include <iostream>
#include <string>

namespace plazy
{
class Exception
{
public:
    void output() const
    {
        std::cerr << "Compile failed\n";
        output_message();
    }

protected:
    virtual void output_message() const = 0;
};

class FileOpenFailed : public Exception
{
public:
    FileOpenFailed(const std::string& file_name) : file_name(file_name)
    {
    }

private:
    virtual void output_message() const override
    {
        std::cerr << "Cannot read file: " << file_name << std::endl;
    }

private:
    std::string file_name;
};

class InvalidWord : public Exception
{
public:
    InvalidWord(const std::string& word) : word(word)
    {
    }

private:
    virtual void output_message() const override
    {
        std::cerr << "Invalid word: " << word << std::endl;
    }

private:
    std::string word;
};

class UnknownOperator : public Exception
{
public:
    UnknownOperator(const std::string& op) : op(op)
    {
    }

private:
    virtual void output_message() const override
    {
        std::cerr << "Unknown operator: " << op << std::endl;
    }

private:
    std::string op;
};

class UnknownDelimiter : public Exception
{
public:
    UnknownDelimiter(const std::string& delim) : delim(delim)
    {
    }

    virtual void output_message() const override
    {
        std::cerr << "Unknown delimiter: " << delim << std::endl;
    }

private:
    std::string delim;
};

class UnknownWord : public Exception
{
public:
    UnknownWord(const std::string& word) : word(word)
    {
    }

private:
    virtual void output_message() const override
    {
        std::cerr << "Unknown word: " << word << std::endl;
    }

private:
    std::string word;
};

class SizeMismatch : public Exception
{
public:
    SizeMismatch(const std::string& msg) : msg(msg)
    {
    }

private:
    virtual void output_message() const override
    {
        std::cerr << "Size mismatch: " << msg << std::endl;
    }

private:
    std::string msg;
};
}  // namespace plazy