#pragma once

#include"Validator.h"

class ArithmeticExpression
{
	string in;
	Validator* validator;
	TQueue<Lexem> infix;
	TQueue<Lexem> posfix;
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
			infix = validator->getValidatedOut();
			cout << "Done";
		}
		catch (...)
		{
			cout << "Error";
		}
	}
};