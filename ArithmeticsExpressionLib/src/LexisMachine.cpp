#include"LexisMachine.h"

LexisMachine::LexisMachine() : Handler(), state(0){
	next = new int* [2];
	call = new Func * [2];
	for (size_t i = 0; i < 2; i++)
	{
		next[i] = new int[2];
		call[i] = new Func[2];
	}
	call[0][0] = &LexisMachine::pushOperator;
	call[0][1] = &LexisMachine::setValue;
	call[1][0] = &LexisMachine::pushValueAndOperator;
	call[1][1] = &LexisMachine::increaseValue;

	next[0][0] = 0;
	next[0][1] = 1;
	next[1][0] = 0;
	next[1][1] = 1;
}
LexisMachine::LexisMachine(Handler* _handler) : Handler(_handler), state(0)
{
	next = new int* [2];
	call = new Func * [2];
	for (size_t i = 0; i < 2; i++)
	{
		next[i] = new int[2];
		call[i] = new Func[2];
	}

	call[0][0] = &LexisMachine::pushOperator;
	call[0][1] = &LexisMachine::setValue;
	call[1][0] = &LexisMachine::pushValueAndOperator;
	call[1][1] = &LexisMachine::increaseValue;

	next[0][0] = 0;
	next[0][1] = 1;
	next[1][0] = 0;
	next[1][1] = 1;
}
LexisMachine::LexisMachine(const LexisMachine& lm) : Handler(lm)
{
	in = lm.in;
	value = lm.value;
	out = lm.out;
	state = lm.state;

	next = new int* [2];
	call = new Func * [2];

	for (size_t i = 0; i < 2; i++)
	{
		next[i] = new int[2];
		call[i] = new Func[2];
		for (size_t j = 0; j < 2; j++)
		{
			next[i][j] = lm.next[i][j];
			call[i][j] = lm.call[i][j];
		}
	}
}
LexisMachine& LexisMachine::operator=(const LexisMachine& lm)
{
	if (this == &lm) return *this;
	for (size_t i = 0; i < 2; i++)
	{
		delete[] next[i];
		delete[] call[i];
	}
	delete[] next;
	delete[] call;


	in = lm.in;
	value = lm.value;
	out = lm.out;
	state = lm.state;
	next = lm.next;

	next = new int* [2];
	call = new Func * [2];

	for (size_t i = 0; i < 2; i++)
	{
		next[i] = new int[2];
		call[i] = new Func[2];
		for (size_t j = 0; j < 2; j++)
		{
			next[i][j] = lm.next[i][j];
			call[i][j] = lm.call[i][j];
		}
	}

	return *this;
}

LexisMachine::~LexisMachine()
{
	for (size_t i = 0; i < 2; i++)
	{
		delete[] next[i];
		delete[] call[i];
	}
	delete[] next;
	delete[] call;
}

void LexisMachine::run(ISolver* solver)
{
	in = solver->getIn();
	out = TQueue<Lexem>(in.size());

	for (size_t i = 0; i < in.size(); i++)
	{
		try
		{
			(this->*call[state][findTransitionColumn(in[i])])(i);
			state = next[state][findTransitionColumn(in[i])];
		}
		catch (...)
		{
			solver->getErrors().emplace_back(LanguageException(
				"Выражение имеет элемент, который не может быть считан:"+ string(1, in[i]) + ", по индексу: " + to_string(i)
			));
		}
	}

	//for no unnecessary places in queue
	TQueue<Lexem>_(out);

	int outSize = 1;
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


	if(solver->getErrors().empty())
	{
		solver->getInfix() = resultOut;


		Handler::run(solver);
	} 
	else
	{
		for (ArithmeticException error : solver->getErrors())
		{
			cout << error.what() << endl;
		}
		solver->getErrors().clear();
		throw LanguageException("LexisError");
	}
}







void LexisMachine::pushOperator(int i) {
	value = Lexem(in[i]);
	out.push(value);
}
void LexisMachine::setValue(int i)
{
	value = Lexem(in[i] - '0');
	if (i == in.size() - 1)
		pushValue(i);
}
void LexisMachine::increaseValue(int i)
{
	value.getValue() = value.getValue() * 10 + in[i] - '0';
	value.getLength()++;
	if (i == in.size() - 1)
		pushValue(i);
}
void LexisMachine::pushValue(int i)
{
	out.push(value);
	value.getValue() = 0;
	value.getLength() = 0;
}

void LexisMachine::pushValueAndOperator(int i)
{
	if (value.getLength() != 0)
		pushValue(i);
	pushOperator(i);
}

int LexisMachine::findTransitionColumn(char c)
{
	switch (c)
	{
	case'0':case'1':case'2':case'3':case'4':case'5':case'6':case'7':case'8':case'9':
		return 1;
	case'+':case'-':case'*':case'/':case'(':case')':
		return 0;

	}
	throw"not in Alphabet";
}
