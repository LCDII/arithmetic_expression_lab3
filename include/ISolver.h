#pragma once
#include"TQueue.h"
#include<string>
#include<vector>
#include"Exceptions.h"
#include"ExprTree.h"



class ArithmeticExpression;
class Lexem;


class ISolver
{
protected:
	ArithmeticExpression* ae;
	std::string in;
	vector<ArithmeticException> errors;
	TQueue<Lexem> infix;
	int answer;

	Expr* root;
public:
	ISolver(ArithmeticExpression* _ae);
	virtual void solve() = 0;
	const string getIn();
	TQueue<Lexem>& getInfix();

	Expr*& getTree();

	vector<ArithmeticException>& getErrors();
	int& getAnswer();
	void setAE(ArithmeticExpression* _ae);
};