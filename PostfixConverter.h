#pragma once

#include"TStack.h"
#include"TQueue.h"
#include <map>
#include"Lexem.h"

class PostfixConverter
{
	TQueue<Lexem> in;
	TQueue<Lexem> out;
	map<char, int> priority;
	int st_size;
public:
	PostfixConverter()
	{

	}
	PostfixConverter(TQueue<Lexem> _in):in(_in)
	{
		priority = { {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'(', 0}};
		st_size = 0;
		out = TQueue<Lexem>(in);
		while (!out.isEmpty())
		{
			out.pop();
			st_size++;
		}
	}

	void convert()
	{
		TStack<Lexem> st(st_size);
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
	}

	TQueue<Lexem>& getOut()
	{
		return out;
	}

};