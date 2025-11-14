#pragma once

#include"Handler.h"
#include<string>
#include"TQueue.h"
#include"Lexem.h"
using namespace std;

class ISolver;
class LexisMachine : public Handler
{
	string in;
	TQueue<Lexem> out;

	using Func = void (LexisMachine::*)(int);
	Func** call;

	int** next;
	int state;

	Lexem value;


	void pushOperator(int i);
	void setValue(int i);
	void increaseValue(int i);
	void pushValue(int i);
	void pushValueAndOperator(int i);

	int findTransitionColumn(char c);


public:
	LexisMachine();
	LexisMachine(Handler* _handler);
	LexisMachine(const LexisMachine& lm);
	LexisMachine& operator=(const LexisMachine& lm);
	~LexisMachine();

	virtual void run(ISolver* solver);
};