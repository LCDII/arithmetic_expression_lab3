#pragma once

#include"Lexem.h"
#include"IFinalStateMachine.h"
#include"TQueue.h"
#include"TStack.h"
#include<string>


using namespace std;

template<typename T>
TStack<T> operator+(const TStack<T>& s1, const TStack<T>& s2) {
	if (s1.isEmpty()) return s2;
	if (s2.isEmpty()) return s1;

	int resultSize = 0;
	vector<T> uniqueElements;


	auto addUniqueElements = [&uniqueElements, &resultSize](const TStack<T>& s) {
		TStack<T> tmp = s;

		while (!tmp.isEmpty()) {
			T current = tmp.top();
			tmp.pop();


			bool found = false;
			for (const auto& elem : uniqueElements) {
				if (elem == current) {
					break;
				}
			}


			if (!found) {
				uniqueElements.insert(uniqueElements.begin(), current);
				resultSize++;
			}
		}
		};

	// Обрабатываем оба стека
	addUniqueElements(s1);
	addUniqueElements(s2);

	TStack<T> result(resultSize);
	// Заполняем результирующий стек
	for (const auto elem : uniqueElements) {
		result.push(elem);
	}

	return result;
}

class LexisMachine : public IFinalStateMachine
{
	using Func = void (LexisMachine::*)(int);
	Func** call;


	TQueue<Lexem> out;
	TStack<int> errors;
	int errorsSize;
	
	string in;
	Lexem value;

	void pushOperator(int i) {
		value = Lexem(in[i]);
		out.push(value);
	}
	void setValue(int i)
	{
		value = Lexem(in[i] - '0');
		if (i == in.size() - 1)
			pushValue(i);
	}
	void increaseValue(int i)
	{
		value.getValue() = value.getValue() * 10 + in[i] - '0';
		value.getLength()++;
		if (i == in.size() - 1)
			pushValue(i);
	}
	void pushValue(int i)
	{
		out.push(value);
		value.getValue() = 0;
		value.getLength() = 0;
	}

	void pushValueAndOperator(int i)
	{
		if (value.getLength() != 0)
			pushValue(i);
		pushOperator(i);
	}

	int findTransitionColumn(char c)
	{
		switch (c)
		{
		case'0':case'1':case'2':case'3':case'4':case'5':case'6':case'7':case'8':case'9':
			return 1;
		case'+':case'-':case'*':case'/':case'(':case')':
			return 0;

		}
		throw"not in Alphabet";
	}


public:
	LexisMachine() : IFinalStateMachine()
	{
		next = new int* [2];
		call = new Func * [2];
		for (size_t i = 0; i < 2; i++)
		{
			next[i] = new int[2];
			call[i] = new Func[2];
		}
	}
	LexisMachine(const string& _in) : IFinalStateMachine(), in(_in)
	{
		if (_in.size() < 1)
			throw - 1;
		errorsSize = 1;
		out = TQueue<Lexem>(in.size());
		next = new int* [2];
		call = new Func * [2];
		for (size_t i = 0; i < 2; i++)
		{
			next[i] = new int[2];
			call[i] = new Func[2];
		}
		
		call[0][0] = &LexisMachine::pushOperator;
		call[0][1] = &LexisMachine::setValue;
		call[1][0] = &LexisMachine::pushValueAndOperator;
		call[1][1] = &LexisMachine::increaseValue;

		next[0][0] = 0;
		next[0][1] = 1;
		next[1][0] = 0;
		next[1][1] = 1;
	}

	LexisMachine(const LexisMachine& lm)
	{
		in = lm.in;
		value = lm.value;
		out = lm.out;
		errorsSize = lm.errorsSize;

		next = new int* [2];
		call = new Func * [2];

		for (size_t i = 0; i < 2; i++)
		{
			next[i] = new int[2];
			call[i] = new Func[2];
			for (size_t j = 0; j < 2; j++)
			{
				next[i][j] = lm.next[i][j];
				call[i][j] = lm.call[i][j];
			}
		}
	}

	LexisMachine& operator=(const LexisMachine& lm)
	{
		if (this == &lm) return *this;
		for (size_t i = 0; i < 2; i++)
		{
			delete[] next[i];
			delete[] call[i];
		}
		delete[] next;
		delete[] call;


		in = lm.in;
		value = lm.value;
		out = lm.out;
		errorsSize = lm.errorsSize;

		next = new int* [2];
		call = new Func * [2];

		for (size_t i = 0; i < 2; i++)
		{
			next[i] = new int[2];
			call[i] = new Func[2];
			for (size_t j = 0; j < 2; j++)
			{
				next[i][j] = lm.next[i][j];
				call[i][j] = lm.call[i][j];
			}
		}

		return *this;
	}

	~LexisMachine()
	{
		for (size_t i = 0; i < 2; i++)
		{
			delete[] next[i];
			delete[] call[i];
		}
		delete[] next;
		delete[] call;
	}

	TQueue<Lexem> getOut()
	{
		return out;
	}
	TStack<int>& getErrors()
	{
		return errors;
	}

	virtual void validate()
	{
		for (size_t i = 0; i < in.size(); i++)
		{
			try
			{
				(this->*call[state][findTransitionColumn(in[i])])(i);
				state = next[state][findTransitionColumn(in[i])];
			}
			catch (...)
			{
				if (errors.isFull())
					errorsSize++;
				
				TStack<int>error;
				error.push(i);
				errors = errors + error;
				//cout << errors;
			}
		}
		cout << "Done"<<endl;
	}


	
};