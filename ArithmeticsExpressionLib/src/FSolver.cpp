
#include"Solver.h"
#include"FSolver.h"
#include"LexisMachine.h"
#include"SyntaxisMachine.h"
#include"PostfixConverter.h"
#include"AnswerGiver.h"
#include"Handler.h"

Solver* FSolver::solver = nullptr;

ISolver* FSolver::getSolver(ArithmeticExpression* _ae)
{
	if (solver == nullptr)
	{
		solver = new Solver(_ae);
		solver->setHandler(new LexisMachine(
					       new SyntaxisMachine(
						   new PostfixConverter(
						   new AnswerGiver()
						   ))));
	}
	return solver;
}