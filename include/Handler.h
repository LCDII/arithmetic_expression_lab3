#pragma once
#include"ISolver.h"



class Handler
{
protected:
	Handler* next;
public:
	Handler();
	Handler(Handler* _next);
	Handler(const Handler& handler);
	~Handler();

	virtual void run(ISolver* solver);
	void add(Handler* _next);
};