

#include "SyntaxisMachine.h"
#include "FSolver.h"

// -------------------- AST helpers --------------------

int SyntaxisMachine::priority(char op)
{
	if (op == '+' || op == '-') return 1;
	if (op == '*' || op == '/') return 2;
	return 0;
}

void SyntaxisMachine::makeOperation(char op)
{
	Expr* right = treeStack.pop();
	Expr* left = treeStack.pop();
	treeStack.push(new BiOperation(op, left, right));
}

Expr* SyntaxisMachine::getTree()
{
	return root;
}

// -----------------------------------------------------

SyntaxisMachine::SyntaxisMachine() : Handler(), state(0), errorIndex(0)
{
	next = new int* [3];
	call = new Func * [3];

	for (size_t i = 0; i < 3; i++)
	{
		next[i] = new int[4];
		call[i] = new Func[4];
	}

	next[0][0] = 0; next[0][1] = 1; next[0][2] = 2; next[0][3] = 1;
	next[1][0] = 0; next[1][1] = 1; next[1][2] = 2; next[1][3] = 1;
	next[2][0] = 0; next[2][1] = 1; next[2][2] = 2; next[2][3] = 1;

	call[0][0] = &SyntaxisMachine::PushLexem;
	call[0][1] = &SyntaxisMachine::pushCloseBracketExcept;
	call[0][2] = &SyntaxisMachine::pushOperatorUn;
	call[0][3] = &SyntaxisMachine::PushLexem;

	call[1][0] = &SyntaxisMachine::pushOpenBracketExcept;
	call[1][1] = &SyntaxisMachine::PushLexem;
	call[1][2] = &SyntaxisMachine::PushLexem;
	call[1][3] = &SyntaxisMachine::pushNumberExcept;

	call[2][0] = &SyntaxisMachine::PushLexem;
	call[2][1] = &SyntaxisMachine::pushCloseBracketExcept;
	call[2][2] = &SyntaxisMachine::pushOperatorExcept;
	call[2][3] = &SyntaxisMachine::PushLexem;
}

SyntaxisMachine::SyntaxisMachine(Handler* _handler) : SyntaxisMachine()
{
	Handler::operator=(*_handler);
}

SyntaxisMachine::~SyntaxisMachine()
{
	for (size_t i = 0; i < 3; i++)
	{
		delete[] next[i];
		delete[] call[i];
	}
	delete[] next;
	delete[] call;
}

SyntaxisMachine::SyntaxisMachine(const SyntaxisMachine& sm) : Handler(sm)
{
	*this = sm;
}

SyntaxisMachine& SyntaxisMachine::operator=(const SyntaxisMachine& sm)
{
	if (this == &sm) return *this;

	in = sm.in;
	errorIndex = sm.errorIndex;
	state = sm.state;
	solver = sm.solver;

	return *this;
}

// -----------------------------------------------------

void SyntaxisMachine::run(ISolver* _solver)
{
	solver = _solver;
	in = solver->getInfix();

	treeStack = TStack<Expr*>(in.getMaxSize());
	opStack = TStack<char>(in.getMaxSize());

	bracketsClosed = TStack<int>(in.getMaxSize());
	bracketsOpened = TStack<int>(in.getMaxSize());

	while (!in.isEmpty())
	{
		Lexem item = in.pop();

		(this->*call[state][findTransitionColumn(item)])(item);

		state = next[state][findTransitionColumn(item)];
	}

	// добиваем стек операторов
	while (!opStack.isEmpty())
		makeOperation(opStack.pop());

	root = treeStack.pop();

	// проверка скобок
	while (!bracketsOpened.isEmpty())
	{
		solver->getErrors().emplace_back(SyntaxisException("Нет закрывающей скобки!"));
		bracketsOpened.pop();
	}

	while (!bracketsClosed.isEmpty())
	{
		solver->getErrors().emplace_back(SyntaxisException("Нет открывающей скобки!"));
		bracketsClosed.pop();
	}

	if (solver->getErrors().empty())
	{
		solver->getTree() = root;

		state = 0;
		errorIndex = 0;

		Handler::run(solver);
	}
	else
	{
		for (auto& error : solver->getErrors())
			cout << error.what() << endl;

		solver->getErrors().clear();

		state = 0;
		errorIndex = 0;
		bracketsOpened.clear();
		bracketsClosed.clear();

		throw SyntaxisException("Syntaxis error");
	}
}

// -----------------------------------------------------

int SyntaxisMachine::findTransitionColumn(Lexem lex)
{
	if (lex.IsNum()) return 3;
	if (char(lex.getValue()) == ')') return 1;
	if (char(lex.getValue()) == '(') return 0;
	return 2;
}

// -----------------------------------------------------

void SyntaxisMachine::PushLexem(Lexem& lex)
{
	if (lex.IsNum())
	{
		treeStack.push(new Number(lex.getValue()));
		errorIndex += lex.getLength();
		return;
	}

	char c = char(lex.getValue());

	if (c == '(')
	{
		bracketsOpened.push(errorIndex);
		opStack.push('(');
	}
	else if (c == ')')
	{
		try { bracketsOpened.pop(); }
		catch (...) { bracketsClosed.push(errorIndex); }

		while (!opStack.isEmpty() && opStack.top() != '(')
			makeOperation(opStack.pop());

		if (!opStack.isEmpty())
			opStack.pop();
	}
	else if (in.getActualSize() == 0)
	{
		solver->getErrors().emplace_back(SyntaxisException(
			"В выражении по индексу: " + to_string(errorIndex) + " присутствует синтаксическая ошибка: " + string(1, lex.getValue()) + ". Оператор не может завершать выражение!"
		));//this or do final state in machine (will ask)
	}
	else
	{
		while (!opStack.isEmpty() && priority(opStack.top()) >= priority(c))
			makeOperation(opStack.pop());

		opStack.push(c);
	}

	errorIndex++;
}

// ----------- ВАЖНО: УНАРНЫЙ МИНУС ------------

void SyntaxisMachine::pushOperatorUn(Lexem& lex)
{
	char c = char(lex.getValue());

	if (c == '+' || c == '-')
	{
		lex.setUn();

		// превращаем в (0 - x)
		treeStack.push(new Number(0));
		opStack.push(c);

		errorIndex++;
	}
	else
	{
		pushOperatorExcept(lex);
	}
}

// -----------------------------------------------------

void SyntaxisMachine::pushOperatorExcept(Lexem& lex)
{
	solver->getErrors().emplace_back(SyntaxisException(
		"В выражении по индексу: " + to_string(errorIndex) + " присутствует синтаксическая ошибка: " + string(1, lex.getValue()) + ". Оператор не может стоять здесь!"
	));
	errorIndex++;
}

void SyntaxisMachine::pushOpenBracketExcept(Lexem& lex)
{
	bracketsOpened.push(errorIndex);
	opStack.push('(');

	solver->getErrors().emplace_back(SyntaxisException(
		"В выражении по индексу: " + to_string(errorIndex) + " присутствует синтаксическая ошибка: " + string(1, lex.getValue()) + ". Скобка не может стоять здесь!"
	));
	errorIndex++;
}

void SyntaxisMachine::pushCloseBracketExcept(Lexem& lex)
{
	try { bracketsOpened.pop(); }
	catch (...) { bracketsClosed.push(errorIndex); }

	while (!opStack.isEmpty() && opStack.top() != '(')
		makeOperation(opStack.pop());

	if (!opStack.isEmpty())
		opStack.pop();

	solver->getErrors().emplace_back(SyntaxisException(
		"В выражении по индексу: " + to_string(errorIndex) + " присутствует синтаксическая ошибка: " + string(1, lex.getValue()) + ". Скобка не может стоять здесь!"
	));
	errorIndex++;
}

void SyntaxisMachine::pushNumberExcept(Lexem& lex)
{
	solver->getErrors().emplace_back(SyntaxisException(
		"В выражении по индексу: " + to_string(errorIndex) + " присутствует синтаксическая ошибка: " + to_string(lex.getValue()) + ". Число не может стоять здесь!"
	));
	errorIndex += lex.getLength() - 1;
}