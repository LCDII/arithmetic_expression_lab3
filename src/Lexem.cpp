#include"Lexem.h"



Lexem::Lexem()
{
	length = 0;
}
Lexem::Lexem(int in)
{
	isBin = false;
	isNum = true;
	value = in;
	length = 1;
}
Lexem::Lexem(char in)
{
	isBin = true;
	isNum = false;
	value = (int)in;
	length = 1;
}
Lexem::Lexem(const Lexem& lex)
{
	isBin = lex.isBin;
	isNum = lex.isNum;
	value = lex.value;
	length = lex.length;
}
int& Lexem::getLength()
{
	return length;
}
bool Lexem::IsNum()
{
	return isNum;
}
bool Lexem::IsBin()
{
	return isBin;
}
int& Lexem::getValue()
{
	return value;
}

void Lexem::setUn()
{
	isBin = false;
}

ostream& operator<<(ostream& ostr, const Lexem& l)
{
	if (l.isNum)
		cout << l.value;
	else
		cout << char(l.value);
	cout << " ";
	return ostr;
}