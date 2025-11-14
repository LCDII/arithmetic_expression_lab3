#pragma once
#include <stdexcept>
using namespace std;

struct ArithmeticException : public runtime_error
{
	ArithmeticException(const string& msg) : runtime_error(msg)
	{}
};

struct LanguageException : public ArithmeticException {
	LanguageException(const string& msg) : ArithmeticException(msg)
	{}
};

struct SyntaxisException : public ArithmeticException {
	SyntaxisException(const string& msg) : ArithmeticException(msg)
	{}
};

struct NoHandlersException : public runtime_error
{
	NoHandlersException(const string& msg) : runtime_error(msg)
	{ }
};

struct NoNextHandlersException : public runtime_error
{
	NoNextHandlersException(const string& msg) : runtime_error(msg)
	{
	}
};