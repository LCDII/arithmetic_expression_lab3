#pragma once
#include"TQueue.h"
#include<string>
#include<vector>
#include"Exceptions.h"



class ArithmeticExpression;
class Lexem;


class ISolver
{
protected:
	ArithmeticExpression* ae;
	std::string in;
	vector<ArithmeticException> errors;
	TQueue<Lexem> infix;
	TQueue<Lexem> postfix;
	int answer;
public:
	ISolver(ArithmeticExpression* _ae);
	virtual void solve() = 0;
	const string getIn();
	TQueue<Lexem>& getInfix();
	TQueue<Lexem>& getPostfix();
	vector<ArithmeticException>& getErrors();
	int& getAnswer();
};