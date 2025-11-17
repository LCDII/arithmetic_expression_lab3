#pragma once
#include<string>
#include"TQueue.h"
#include"Lexem.h"
#include<iostream>

class ISolver;
class ArithmeticExpression
{
	std::string in;
	TQueue<Lexem> infix;
	TQueue<Lexem> postfix;
	ISolver* solver;
	int answer;
public:
	ArithmeticExpression(std::string _in);
	ArithmeticExpression(const ArithmeticExpression& ae);
	ArithmeticExpression& operator=(const ArithmeticExpression& ae);
	~ArithmeticExpression();
	string getIn();
	TQueue<Lexem> getInfix();
	TQueue<Lexem> getPostfix();
	int getAnswer();

	ArithmeticExpression operator+(const ArithmeticExpression& ae);
	ArithmeticExpression operator-(const ArithmeticExpression& ae);
	ArithmeticExpression operator*(const ArithmeticExpression& ae);
	ArithmeticExpression operator/(const ArithmeticExpression& ae);

	ArithmeticExpression operator+(const string& s);
	ArithmeticExpression operator-(const string& s);
	ArithmeticExpression operator*(const string& s);
	ArithmeticExpression operator/(const string& s);

	ArithmeticExpression operator+(const int& s);
	ArithmeticExpression operator-(const int& s);
	ArithmeticExpression operator*(const int& s);
	ArithmeticExpression operator/(const int& s);

	friend std::ostream& operator<<(std::ostream& ostr, ArithmeticExpression ae);

};