#pragma once

#include"Handler.h"
#include"TQueue.h"
#include"Lexem.h"
#include<map>
using namespace std;

class ISolver;
class PostfixConverter : public Handler
{
	TQueue<Lexem> in;
	TQueue<Lexem> out;
	map<char, int> priority;
	int st_size;
public:
	PostfixConverter();
	PostfixConverter(Handler* _handler);
	PostfixConverter(const PostfixConverter& pc);
	virtual void run(ISolver* solver);
};