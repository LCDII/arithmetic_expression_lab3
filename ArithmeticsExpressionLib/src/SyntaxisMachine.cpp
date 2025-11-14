#include "SyntaxisMachine.h"


SyntaxisMachine::SyntaxisMachine() : Handler(), state(0), errorIndex(0)
{
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

	call[0][0] = &SyntaxisMachine::PushLexem;
	call[0][1] = &SyntaxisMachine::pushCloseBracketExcept;
	call[0][2] = &SyntaxisMachine::pushOperatorUn;
	call[0][3] = &SyntaxisMachine::PushLexem;
	call[1][0] = &SyntaxisMachine::pushOpenBracketExcept;
	call[1][1] = &SyntaxisMachine::PushLexem;
	call[1][2] = &SyntaxisMachine::PushLexem;
	call[1][3] = &SyntaxisMachine::pushNumberExcept;
	call[2][0] = &SyntaxisMachine::PushLexem;
	call[2][1] = &SyntaxisMachine::pushCloseBracketExcept;
	call[2][2] = &SyntaxisMachine::pushOperatorExcept;
	call[2][3] = &SyntaxisMachine::PushLexem;
}
SyntaxisMachine::SyntaxisMachine(Handler* _handler) : Handler(_handler), state(0), errorIndex(0)
{
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

	call[0][0] = &SyntaxisMachine::PushLexem;
	call[0][1] = &SyntaxisMachine::pushCloseBracketExcept;
	call[0][2] = &SyntaxisMachine::pushOperatorUn;
	call[0][3] = &SyntaxisMachine::PushLexem;
	call[1][0] = &SyntaxisMachine::pushOpenBracketExcept;
	call[1][1] = &SyntaxisMachine::PushLexem;
	call[1][2] = &SyntaxisMachine::PushLexem;
	call[1][3] = &SyntaxisMachine::pushNumberExcept;
	call[2][0] = &SyntaxisMachine::PushLexem;
	call[2][1] = &SyntaxisMachine::pushCloseBracketExcept;
	call[2][2] = &SyntaxisMachine::pushOperatorExcept;
	call[2][3] = &SyntaxisMachine::PushLexem;
}


SyntaxisMachine::~SyntaxisMachine()
{
	for (size_t i = 0; i < 3; i++)
	{
		delete[] next[i];
		delete[] call[i];
	}
	delete[] next;
	delete[] call;
}
SyntaxisMachine::SyntaxisMachine(const SyntaxisMachine& sm) : Handler(sm)
{
	in = sm.in;
	out = sm.out;
	errorIndex = sm.errorIndex;
	state = sm.state;
	solver = sm.solver;


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
SyntaxisMachine& SyntaxisMachine::operator=(const SyntaxisMachine& sm)
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
	state = sm.state;
	solver = sm.solver;
	next = sm.next;


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



//---------------------------------------------------------------------------------------------------------------------------




void SyntaxisMachine::run(ISolver* _solver)
{
	solver = _solver;
	in = solver->getInfix();
	out = TQueue<Lexem>(in);
	int st_size = 1;
	while (!out.isEmpty())
	{
		st_size++;
		out.pop();
	}
	bracketsClosed = TStack<int>(st_size);
	bracketsOpened = TStack<int>(st_size);

	while (!in.isEmpty())
	{
		Lexem item = in.pop();

		(this->*call[state][findTransitionColumn(item)])(item);
		state = next[state][findTransitionColumn(item)];
	}
	while (!bracketsOpened.isEmpty())
	{
		solver->getErrors().emplace_back(SyntaxisException(
			"В выражении по индексу: " + to_string(bracketsOpened.pop()) + " присутствует синтаксическая ошибка: " + "(. Нет закрывающей скобки!"
		));
	}
	while (!bracketsClosed.isEmpty())
	{
		solver->getErrors().emplace_back(SyntaxisException(
			"В выражении по индексу: " + to_string(bracketsClosed.pop()) + " присутствует синтаксическая ошибка: " + "). Нет открывающей скобки!"
		));
	}

	if(solver->getErrors().empty())
	{
		solver->getInfix() = out;
		Handler::run(solver);
	}
	else
	{
		for (ArithmeticException error : solver->getErrors())
		{
			cout << error.what() << endl;
		}
		solver->getErrors().clear();
		throw SyntaxisException("Syntaxis error");
	}
}

//---------------------------------------------------------------------------------------------------------------------------


int SyntaxisMachine::findTransitionColumn(Lexem lex)
{
	if (lex.IsNum())
		return 3;
	else if (char(lex.getValue()) == ')')
		return 1;
	else if (char(lex.getValue()) == '(')
		return 0;
	else
		return 2;
}

/*
			| (  | )  | /*+- | num |
		0	| f1 | f5 |  f2  | f1  |
		1	| f4 | f1 |  f1  | f6  |
		2	| f1 | f5 |  f3  | f1  |
	*/


void SyntaxisMachine::PushLexem(Lexem& lex)//f1 //for all non except pushes
{
	out.push(lex);
	if (lex.IsNum())
		errorIndex += lex.getLength();
	else if (char(lex.getValue()) == '(')
	{
		bracketsOpened.push(errorIndex);
		errorIndex++;
	}
	else if (char(lex.getValue()) == ')')
	{
		try {
			bracketsOpened.pop();
		}
		catch (...)
		{
			bracketsClosed.push(errorIndex);
		}
		errorIndex++;
	}
	else
		errorIndex++;
}
void SyntaxisMachine::pushOperatorUn(Lexem& lex)//f2
{
	if (char(lex.getValue()) == '+' || char(lex.getValue()) == '-')
		lex.setUn();
	else
		pushOperatorExcept(lex);
	out.push(lex);
	errorIndex++;
}
void SyntaxisMachine::pushOperatorExcept(Lexem& lex)//f3
{
	out.push(lex);

	solver->getErrors().emplace_back(SyntaxisException(
		"В выражении по индексу: " + to_string(errorIndex) + " присутствует синтаксическая ошибка: " + string(1, lex.getValue()) +". Оператор не может стоять здесь!"
	));
	errorIndex++;
}
void SyntaxisMachine::pushOpenBracketExcept(Lexem& lex)//f4
{
	out.push(lex);
	bracketsOpened.push(errorIndex);
	solver->getErrors().emplace_back(SyntaxisException(
		"В выражении по индексу: " + to_string(errorIndex) + " присутствует синтаксическая ошибка: " + string(1, lex.getValue())+". Скобка не может стоять здесь!"
	));
	errorIndex++;

}
void SyntaxisMachine::pushCloseBracketExcept(Lexem& lex)//f5
{
	out.push(lex);
	try {
		bracketsOpened.pop();
	}
	catch (...)
	{
		bracketsClosed.push(errorIndex);
	}
	solver->getErrors().emplace_back(SyntaxisException(
		"В выражении по индексу: " + to_string(errorIndex) + " присутствует синтаксическая ошибка: " + string(1, lex.getValue())+". Скобка не может стоять здесь!"
	));
	errorIndex++;

}
void SyntaxisMachine::pushNumberExcept(Lexem& lex)//f6       cant happen with [56, 76] but can happen with  [ ) , 56] in queue
{
	out.push(lex);
	solver->getErrors().emplace_back(SyntaxisException(
		"В выражении по индексу: " + to_string(errorIndex) + " присутствует синтаксическая ошибка: " + to_string(lex.getValue())+". Число не может стоять здесь!"
	));

	errorIndex += lex.getLength()-1;
}

