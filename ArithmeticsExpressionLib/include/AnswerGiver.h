#pragma once


#include"Handler.h"
#include"TQueue.h"
#include"Lexem.h"

class ISolver;
class AnswerGiver : public Handler 
{
	TQueue<Lexem> in;
	int out;
public:
	AnswerGiver();
	AnswerGiver(Handler* _handler);
	AnswerGiver(const AnswerGiver& ag);
	virtual void run(ISolver* solver);
};