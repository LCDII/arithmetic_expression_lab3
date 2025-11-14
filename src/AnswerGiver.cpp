#include "AnswerGiver.h"
#include"TStack.h"

AnswerGiver::AnswerGiver() : Handler(), out(0){}
AnswerGiver::AnswerGiver(Handler* _handler) : Handler(_handler), out(0)
{

}
AnswerGiver::AnswerGiver(const AnswerGiver& ag):Handler(ag)
{
	in = ag.in;
	out = ag.out;
}

void AnswerGiver::run(ISolver* solver)
{
	in = solver->getPostfix();
	int st_size = 1;
	TQueue<Lexem>_(in);
	while (!_.isEmpty())
	{
		_.pop();
		st_size++;
	}

	TStack<int> stack(st_size);
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