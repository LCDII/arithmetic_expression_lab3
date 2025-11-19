#include"PostfixConverter.h"
#include"TStack.h"


PostfixConverter::PostfixConverter() : Handler()
{
	priority = { {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'(', 0} };
}
PostfixConverter::PostfixConverter(Handler* _handler) : Handler(_handler)
{
	priority = { {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'(', 0} };
}

PostfixConverter::PostfixConverter(const PostfixConverter& pc):Handler(pc)
{
	in = pc.in;
	out = pc.out;
	priority = pc.priority;
}


void PostfixConverter::run(ISolver* solver)
{
	in = solver->getInfix();

	TStack<Lexem> st(in.getActualSize());

	// unar - or +  is  +1 in queue size : [-, 1] -> [0, -, 1], *2 for garant
	out = TQueue<Lexem>(in.getActualSize()*2);

	Lexem stackItem;
	while (!in.isEmpty())
	{
		Lexem inItem = in.pop();
		char value = char(inItem.getValue());
		if (!inItem.IsNum())
		{
			if (value == '(')
			{
				st.push(inItem);
			}
			else if (value == ')')
			{
				stackItem = st.pop();
				while (char(stackItem.getValue()) != '(')
				{
					out.push(stackItem);
					stackItem = st.pop();
				}
			}
			else//ops
			{
				while (!st.isEmpty())
				{
					stackItem = st.pop();
					if (!inItem.IsBin())
					{
						int numBeforeUnar = 0;
						Lexem numBeforeUnarLexem(numBeforeUnar);
						out.push(numBeforeUnarLexem);
					}
					if (priority[value] <= priority[char(stackItem.getValue())])
						out.push(stackItem);
					else
					{
						st.push(stackItem);
						break;
					}

				}
				if (!inItem.IsBin() && st.isEmpty())
				{
					int numBeforeUnar = 0;
					Lexem numBeforeUnarLexem(numBeforeUnar);
					out.push(numBeforeUnarLexem);
				}

				st.push(inItem);
			}
		}
		else
		{
			out.push(inItem);
		}
	}
	while (!st.isEmpty())
	{
		stackItem = st.pop();
		out.push(stackItem);
	}


	solver->getPostfix() = out.refactor();

	Handler::run(solver);
}
