#pragma once

#include"Validator.h"

class ArithmeticExpression
{
	string in;
	Validator* validator;
	TQueue<Lexem> infix;
	TQueue<Lexem> postfix;
	int answer;
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
			answer = validator->getValidatedOut();
			cout << "Done";
		}
		catch (...)
		{
			cout << "Error";
			exit(0);
		}
	}
	int getOut()
	{
		return answer;
	}
};