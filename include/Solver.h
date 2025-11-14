#pragma once

#include"ISolver.h"
class Handler;

class Solver : public ISolver
{
	Handler* handler;
public:
	Solver(ArithmeticExpression* _ae);
	void setHandler(Handler* handler);
	virtual void solve();
};