#include "ArithmeticExpression.h"
#include <string>
#include<iostream>
#include<locale.h>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Ru");
	string s = "1-(-1)";
	string s2 = "56+1";
	string s3 = "5*2";
	ArithmeticExpression ae(s);
	ArithmeticExpression ae1(s2);
	ArithmeticExpression ae2(s3);
	int a = 2;
	cout << ae.getAnswer()<<endl;
	cout << ae1.getAnswer()<<endl;
	cout << "_______________" << endl;

	cout << (ae + "2").getAnswer() << endl;
	cout << (ae - "2").getAnswer() << endl;
	cout << (ae * "2").getAnswer() << endl;
	cout << (ae / "2").getAnswer() << endl;
	cout << "_______________" << endl;

	cout << (ae + ae1).getAnswer() << endl;
	cout << (ae - ae1).getAnswer() << endl;
	cout << (ae * ae1).getAnswer() << endl;
	cout << (ae / ae1).getAnswer() << endl;
	cout << "_______________" << endl;

	cout << (ae + a).getAnswer() << endl;
	cout << (ae - a).getAnswer() << endl;
	cout << (ae * a).getAnswer() << endl;
	cout << (ae / a).getAnswer() << endl;
	cout << "_______________" << endl;
	cout << ae<<endl;
	cout << ae2;
}				  


