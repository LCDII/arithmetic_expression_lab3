#pragma once
#include<iostream>
using namespace std;
class Lexem {
	bool isBin;
	bool isNum;
	int value;
	int length;
public:
	Lexem()
	{
		length = 0;
	}
	Lexem(int in)
	{
		isBin = false;
		isNum = true;
		value = in;
		length = 1;
	}
	Lexem(char in)
	{
		isBin = true;
		isNum = false;
		value = (int)in;
		length = 1;
	}
	Lexem(const Lexem& lex)
	{
		isBin = lex.isBin;
		isNum = lex.isNum;
		value = lex.value;
		length = lex.length;
	}
	int& getLength()
	{
		return length;
	}
	bool IsNum()
	{
		return isNum;
	}
	bool IsBin()
	{
		return isBin;
	}
	int& getValue()
	{
		return value;
	}

	void setUn()
	{
		isBin = false;
	}

	friend ostream& operator<<(ostream& ostr, const Lexem& l)
	{
		if (l.isNum)
			cout << l.value;
		else
			cout << char(l.value);
		cout << " ";
		return ostr;
	}
};