#include"ISolver.h"
#include"ArithmeticExpression.h"

ISolver::ISolver(ArithmeticExpression* _ae) : ae(_ae), in(ae->getIn()), answer(0), infix(TQueue<Lexem>()), postfix(TQueue<Lexem>())
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
void ISolver::setAE(ArithmeticExpression* _ae)
{
	ae = _ae;
	in = ae->getIn();
	infix = TQueue<Lexem>();
	postfix = TQueue<Lexem>();
	answer = 0;
	errors.clear();//not neccesary
}
