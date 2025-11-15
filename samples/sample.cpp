#include "ArithmeticExpression.h"
#include <string>
#include<iostream>
#include<locale.h>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Ru");
	string s = "1-(-1)";
	ArithmeticExpression ae(s);
	ArithmeticExpression ae1(ae);
	cout << ae.getAnswer();
	cout << ae1.getAnswer();
}


