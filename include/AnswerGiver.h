#pragma once

#include "Handler.h"
#include "ExprTree.h"

class ISolver;

class AnswerGiver : public Handler
{
public:
    AnswerGiver();
    AnswerGiver(Handler* _handler);
    AnswerGiver(const AnswerGiver& ag);

    virtual void run(ISolver* solver);
};