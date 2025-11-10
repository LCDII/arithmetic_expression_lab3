#pragma once

#include"Validator.h"

class ArithmeticExpression
{
	string in;
	Validator* validator;
	TQueue<Lexem> infix;
	TQueue<Lexem> postfix;
public:
	ArithmeticExpression(string& _n) : in(_n)
	{

	}
	void setValidator(Validator* _validator)
	{
		validator = _validator;
	}
	void validate()
	{
		try
		{
			postfix = validator->getValidatedOut();
			cout << "Done";
		}
		catch (...)
		{
			cout << "Error";
		}
	}
	TQueue<Lexem>& getOut()
	{
		return postfix;
	}
};