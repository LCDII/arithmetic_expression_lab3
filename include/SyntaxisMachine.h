#pragma once

#include "Handler.h"
#include "TQueue.h"
#include "TStack.h"
#include "Lexem.h"
#include "ExprTree.h"

class ISolver;

class SyntaxisMachine : public Handler
{
    TQueue<Lexem> in;

    using Func = void (SyntaxisMachine::*)(Lexem&);
    Func** call;

    int** next;
    int state;

    int errorIndex;
    TStack<int> bracketsOpened;
    TStack<int> bracketsClosed;
    ISolver* solver;

    // ----------------------
    TStack<Expr*> treeStack;
    TStack<char> opStack;
    Expr* root;
    // -----------------------

    int findTransitionColumn(Lexem lex);

    void PushLexem(Lexem& lex);
    void pushOperatorUn(Lexem& lex);
    void pushOperatorExcept(Lexem& lex);
    void pushOpenBracketExcept(Lexem& lex);
    void pushCloseBracketExcept(Lexem& lex);
    void pushNumberExcept(Lexem& lex);

    // ----------------------
    void makeOperation(char op);
    int priority(char op);
    // ---------------------------

public:
    SyntaxisMachine();
    SyntaxisMachine(Handler* _handler);
    ~SyntaxisMachine();
    SyntaxisMachine(const SyntaxisMachine& sy);
    SyntaxisMachine& operator=(const SyntaxisMachine& sy);

    virtual void run(ISolver* solver);

    // ----------------------
    Expr* getTree();
};