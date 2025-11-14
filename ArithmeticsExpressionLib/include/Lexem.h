#pragma once
#include<iostream>
using namespace std;

class Lexem {
	bool isBin;
	bool isNum;
	int value;
	int length;
public:
	Lexem();
	Lexem(int in);
	Lexem(char in);
	Lexem(const Lexem& lex);
	int& getLength();
	bool IsNum();
	bool IsBin();
	int& getValue();

	void setUn();

	friend ostream& operator<<(ostream& ostr, const Lexem& l);
};