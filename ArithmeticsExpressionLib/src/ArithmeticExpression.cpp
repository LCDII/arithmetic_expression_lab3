#include"ArithmeticExpression.h"
#include"FSolver.h"
#include"ISolver.h"
#include"Exceptions.h"
using namespace std;


ArithmeticExpression::ArithmeticExpression(string _in) : in(_in)
{
	if (in.size() < 1)
		throw "Arithmetics Expression cannot be empty";
	//or we can just set in as 0
	solver = FSolver::getSolver(this);

	try
	{
		solver->solve();
	}
	catch (NoHandlersException nh)
	{
		cout << nh.what()<<endl;
		throw nh;
	}
	catch (NoNextHandlersException nnh)
	{
		infix = solver->getInfix();
		postfix = solver->getPostfix();
		answer = solver->getAnswer();
	}
	catch (LanguageException le)
	{
		cout << le.what()<<endl;
		throw le;
	}
	catch (SyntaxisException se)
	{
		cout << se.what() << endl;
		throw se;
	}
}

ArithmeticExpression::ArithmeticExpression(const ArithmeticExpression& ae)
{
	in = ae.in;
	infix = ae.infix;
	postfix = ae.postfix;
	solver = ae.solver;
	answer = ae.answer;
}

ArithmeticExpression& ArithmeticExpression::operator=(const ArithmeticExpression& ae)
{
	if (this == &ae) return *this;

	in = ae.in;
	infix = ae.infix;
	postfix = ae.postfix;
	solver = ae.solver;
	answer = ae.answer;

	return *this;
}

ArithmeticExpression::~ArithmeticExpression()
{
	solver = nullptr;//Не стоит удалять общий на всю программу solver;
}

string ArithmeticExpression::getIn()
{
	return in;
}

TQueue<Lexem> ArithmeticExpression::getInfix()
{
	return infix;
}

TQueue<Lexem> ArithmeticExpression::getPostfix()
{
	return postfix;
}

int ArithmeticExpression::getAnswer()
{
	return answer;
}