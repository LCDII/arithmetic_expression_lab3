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
	st_size = pc.st_size;
}


void PostfixConverter::run(ISolver* solver)
{
	in = solver->getInfix();
	//--------------------------------------------------------
	TQueue<Lexem>_(in);
	int outSize = 1;
	int operatorsCount = 0;
	while (!_.isEmpty())
	{
		Lexem l = _.pop();
		if (!l.IsNum())
			operatorsCount++;
		outSize++;
	}

	TStack<Lexem> st(operatorsCount);

	outSize += operatorsCount*2;// unar - or +  is  +1 in queue size : [-, 1] -> [0, -, 1], *2 for every operator - garant
	out = TQueue<Lexem>(outSize);
	//------------------------------------------------------------------------
	//That is beacause we do not use Linked List in TQueue

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
			else if (value == '*' || value == '/' || value == '+' || value == '-')
			{
				//"(40*(-15+30)/15)-1"
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

	//------------------------------------------------------------------------
	//That is beacause we do not use Linked List in TQueue
	_ = TQueue<Lexem>(out);

	outSize = 1; 
	while (!_.isEmpty())
	{
		outSize++;
		_.pop();
	}

	TQueue<Lexem> resultOut(outSize);
	while (!out.isEmpty())
	{
		resultOut.push(out.pop());
	}
	//--------------------------------------------------------

	solver->getPostfix() = resultOut;

	Handler::run(solver);
}
