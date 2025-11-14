#include"ISolver.h"
#include"ArithmeticExpression.h"

ISolver::ISolver(ArithmeticExpression* _ae) : ae(_ae), in(ae->getIn()), answer(0)
{

}
const string ISolver::getIn()
{
	return ae->getIn();
}

TQueue<Lexem>& ISolver:: getInfix()
{
	return infix;
}

TQueue<Lexem>& ISolver::getPostfix()
{
	return postfix;
}

int& ISolver::getAnswer()
{
	return answer;
}

vector<ArithmeticException>& ISolver::getErrors()
{
	return errors;
}