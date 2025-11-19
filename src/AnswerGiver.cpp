#include "AnswerGiver.h"
#include"TStack.h"

AnswerGiver::AnswerGiver() : Handler(){}
AnswerGiver::AnswerGiver(Handler* _handler) : Handler(_handler)
{

}
AnswerGiver::AnswerGiver(const AnswerGiver& ag):Handler(ag)
{
	in = ag.in;
}

void AnswerGiver::run(ISolver* solver)
{
	in = solver->getPostfix();

	TStack<int> stack(in.getActualSize());
	while (!in.isEmpty())
	{
		Lexem inItem = in.pop();
		if (inItem.IsNum())
			stack.push(inItem.getValue());
		else
		{
			char c = char(inItem.getValue());
			int n2 = stack.pop();
			int n1 = stack.pop();
			switch (c)
			{
			case'+':
				stack.push(n1 + n2);
				break;
			case'-':
				stack.push(n1 - n2);
				break;
			case'*':
				stack.push(n1 * n2);
				break;
			case'/':
				stack.push(n1 / n2);
				break;
			}
		}
	}

	solver->getAnswer() = stack.pop();


	Handler::run(solver);
}