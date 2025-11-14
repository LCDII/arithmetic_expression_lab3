#pragma once

class ArithmeticExpression;
class Solver;

class FSolver
{
	static Solver* solver;
public:
	FSolver() = default;

	static ISolver* getSolver(ArithmeticExpression* _ae);
};
