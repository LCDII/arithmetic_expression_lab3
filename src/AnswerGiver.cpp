#include "AnswerGiver.h"
#include "ISolver.h"

AnswerGiver::AnswerGiver() : Handler() {}

AnswerGiver::AnswerGiver(Handler* _handler) : Handler(_handler) {}

AnswerGiver::AnswerGiver(const AnswerGiver& ag) : Handler(ag) {}

// -----------------------------------------

void AnswerGiver::run(ISolver* solver)
{
   
    Expr* root = solver->getTree();

    CalcVisitor cv;

    int result = root->accept(&cv);

    solver->getAnswer() = result;

    Handler::run(solver);
}