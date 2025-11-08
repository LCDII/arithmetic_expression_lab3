#pragma once

#include"Lexem.h"
#include"IFinalStateMachine.h"
#include"TQueue.h"
#include"TStack.h"
#include<string>


using namespace std;



class SyntaxisMachine : public IFinalStateMachine
{
	TQueue<Lexem> in;
	TQueue<Lexem> out;
	using Func = void (IFinalStateMachine::*)(Lexem&);
	Func** call;

	TStack<int> errors;
	int errorIndex;
	int findTransitionColumn(Lexem lex)
	{
		if (char(lex.getValue()) == ')')
			return 1;
		else if (char(lex.getValue()) == '(')
			return 0;
		else if (lex.IsNum())
			return 3;
		else
			return 2;

	}

	/*
		q0 = начало строки или (
		q1 = ) или число
		q2 = операторы
	*/
	
	/*
			| (  | )  | /*+- | num |
		0	| f3 | f8 |  f2  | f4  |
		1	| f7 | f5 |  f1  | f9  |
		2	| f3 | f8 |  f6  | f4  |
	*/
	/*
			| (  | )  | /*+- | num |
		0	| f1 | f5 |  f2  | f1  |
		1	| f4 | f1 |  f1  | f6  |
		2	| f1 | f5 |  f3  | f1  |
	*/


	void PushLexem(Lexem& lex)//f1 //for all non except pushes
	{
		out.push(lex);
		if(lex.IsNum())
			errorIndex += lex.getLength();
		else
			errorIndex++;
	}
	void pushOperatorUn(Lexem& lex)//f2
	{
		if (char(lex.getValue()) == '+' || char(lex.getValue()) == '-')
			lex.setUn();
		else
			pushOperatorExcept(lex);
		out.push(lex);
		errorIndex++;
	}
	void pushOperatorExcept(Lexem& lex)//f3
	{
		out.push(lex);

		errors.push(errorIndex);
		errorIndex++;
	}
	void pushOpenBracketExcept(Lexem& lex)//f4
	{
		out.push(lex);

		errors.push(errorIndex);
		errorIndex++;
		
	}
	void pushCloseBracketExcept(Lexem& lex)//f5
	{
		out.push(lex);

		errors.push(errorIndex);
		errorIndex++;
		
	}
	void pushNumberExcept(Lexem& lex)//f6
	{
		out.push(lex); 
		errors.push(errorIndex);

		errorIndex += lex.getLength()-1;
	}



public:
	SyntaxisMachine()
	{
		next = new int* [3];
		call = new Func * [3];
		for (size_t i = 0; i < 3; i++)
		{
			next[i] = new int[4];
			call[i] = new Func[4];
		}
	}
	SyntaxisMachine(const SyntaxisMachine& sm)
	{
		in = sm.in;
		out = sm.out;
		errorIndex = sm.errorIndex;
		errors = sm.errors;


		next = new int* [3];
		call = new Func * [3];

		for (size_t i = 0; i < 3; i++)
		{
			next[i] = new int[4];
			call[i] = new Func[4];
			for (size_t j = 0; j < 4; j++)
			{
				next[i][j] = sm.next[i][j];
				call[i][j] = sm.call[i][j];
			}
		}
	}
	SyntaxisMachine& operator=(const SyntaxisMachine& sm)
	{
		if (this == &sm) return *this;
		for (size_t i = 0; i < 2; i++)
		{
			delete[] next[i];
			delete[] call[i];
		}
		delete[] next;
		delete[] call;

		in = sm.in;
		out = sm.out;
		errorIndex = sm.errorIndex;
		errors = sm.errors;


		next = new int* [3];
		call = new Func * [3];

		for (size_t i = 0; i < 3; i++)
		{
			next[i] = new int[4];
			call[i] = new Func[4];
			for (size_t j = 0; j < 4; j++)
			{
				next[i][j] = sm.next[i][j];
				call[i][j] = sm.call[i][j];
			}
		}
		return *this;
	}
	~SyntaxisMachine()
	{
		for (size_t i = 0; i < 2; i++)
		{
			delete[] next[i];
			delete[] call[i];
		}
		delete[] next;
		delete[] call;
	}
	SyntaxisMachine(TQueue<Lexem>& _in) : in(_in)
	{
		TQueue<Lexem>_(in);
		int outSize = 0;
		while (!_.isEmpty())
		{
			outSize++;
			_.pop();
		}
		errors = TStack<int>(outSize);
		errorIndex = 0;

		outSize *= 2;//потому что каждая унарка добавляет +1 элемент, *2 = гарант
		out = TQueue<Lexem>(outSize);


		
		next = new int* [3];
		call = new Func * [3];
		for (size_t i = 0; i < 3; i++)
		{
			next[i] = new int[4];
			call[i] = new Func[4];
		}


		/*
			| ( | ) | /*+- | num |
		0	| 0 | 1 |   2  |  1  |
		1	| 0 | 1 |   2  |  1  |
		2	| 0 | 1 |   2  |  1  |
		*/
		next[0][0] = 0;
		next[0][1] = 1;
		next[0][2] = 2;
		next[0][3] = 1;
		next[1][0] = 0;
		next[1][1] = 1;
		next[1][2] = 2;
		next[1][3] = 1;
		next[2][0] = 0;
		next[2][1] = 1;
		next[2][2] = 2;
		next[2][3] = 1;


		
		/*
			| (  | )  | /*+- | num |
		0	| f1 | f5 |  f2  | f1  |
		1	| f4 | f1 |  f1  | f6  |
		2	| f1 | f5 |  f3  | f1  |
		*/

		call[0][0] = static_cast<Func>(&SyntaxisMachine::PushLexem);
		call[0][1] = static_cast<Func>(&SyntaxisMachine::pushCloseBracketExcept);
		call[0][2] = static_cast<Func>(&SyntaxisMachine::pushOperatorUn);
		call[0][3] = static_cast<Func>(&SyntaxisMachine::PushLexem);
		call[1][0] = static_cast<Func>(&SyntaxisMachine::pushOpenBracketExcept);
		call[1][1] = static_cast<Func>(&SyntaxisMachine::PushLexem);
		call[1][2] = static_cast<Func>(&SyntaxisMachine::PushLexem);
		call[1][3] = static_cast<Func>(&SyntaxisMachine::pushNumberExcept);
		call[2][0] = static_cast<Func>(&SyntaxisMachine::PushLexem);
		call[2][1] = static_cast<Func>(&SyntaxisMachine::pushCloseBracketExcept);
		call[2][2] = static_cast<Func>(&SyntaxisMachine::pushOperatorExcept);
		call[2][3] = static_cast<Func>(&SyntaxisMachine::PushLexem);
	}
	void setIn(TQueue<Lexem>&_in)
	{
		in = _in;
	}
	TQueue<Lexem>& getOut()
	{
		return out;
	}

	virtual void validate()
	{
		while (!in.isEmpty())
		{
			Lexem item = in.pop();
			(this->*call[state][findTransitionColumn(item)])(item);
			state = next[state][findTransitionColumn(item)];
		}
		cout << "Done"<<endl;
	}

	TStack<int>& getErrors()
	{
		return errors;
	}


};