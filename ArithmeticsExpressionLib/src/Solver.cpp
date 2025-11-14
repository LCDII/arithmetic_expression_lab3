#include"Solver.h"
#include"Handler.h"
#include"Exceptions.h"

Solver::Solver(ArithmeticExpression* _ae) : ISolver(_ae), handler(nullptr) {}

void Solver::solve()
{
	if (handler != nullptr)
		handler->run(this);
	else throw NoHandlersException("Нет обработчиков у объекта ISolver");
}

void Solver::setHandler(Handler* _handler)
{
	handler = _handler;
}