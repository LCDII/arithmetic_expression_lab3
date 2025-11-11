#pragma once

#include"TStack.h"
#include"TQueue.h"
#include"Lexem.h"


class Solver
{
	TQueue<Lexem> in;
	int out;
	int st_size;
public:
	Solver()
	{

	}
	Solver(TQueue<Lexem> _in) : in(_in), st_size(0)
	{
		TQueue<Lexem>_(in);
		while (!_.isEmpty())
		{
			cout<<_.pop();
			st_size++;
		}
	}

	void Solve()
	{
		TStack<int> solver(st_size);
		while (!in.isEmpty())
		{
			Lexem inItem = in.pop();
			if (inItem.IsNum())
				solver.push(inItem.getValue());
			else
			{
				char c = char(inItem.getValue());
				int n2 = solver.pop();
				int n1 = solver.pop();
				switch (c)
				{
				case'+':
					solver.push(n1 + n2);
					break;
				case'-':
					solver.push(n1 - n2);
					break;
				case'*':
					solver.push(n1 * n2);
					break;
				case'/':
					solver.push(n1 / n2);
					break;
				}
			}
		}
		out = solver.pop();
	}

	int getOut()
	{
		return out;
	}
};