#include "ArithmeticExpression.h"
#include <string>
#include<iostream>
#include<locale.h>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Ru");
	string s = "(-1*65+56)-34";
	ArithmeticExpression ae(s);
	cout << ae.getAnswer();
	
}


