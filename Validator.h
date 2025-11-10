#pragma once

#include"LexisMachine.h"
#include"SyntaxisMachine.h"
#include"PostfixConverter.h"




class Validator
{
	LexisMachine lexisMachine;
	SyntaxisMachine syntaxisMachine;
	PostfixConverter postfixConverter;
	string in;
	TStack<int> errors;




	TStack<int> bracketChecker()
	{
		TStack<int> result1(in.size());
		TStack<int> result2(in.size());
		for (size_t i = 0; i < in.size(); i++)
		{
			if (in[i] == '(')
				result1.push(i);
			else if (in[i] == ')')
			{
				try {
					result1.pop();
				}
				catch (...)
				{
					result2.push(i);
				}
			
			}
		}
		TStack<int> result = result1 + result2;
		return result;
	}
    void validate()
    {

        lexisMachine.validate();
        errors = errors + lexisMachine.getErrors();


        errors = errors + bracketChecker();
  

        syntaxisMachine = SyntaxisMachine(lexisMachine.getOut());
        syntaxisMachine.validate();

        errors = errors + syntaxisMachine.getErrors();


    }
public:
    Validator(const string& _in) /*: in(_in), lexisMachine(LexisMachine(in)), syntaxisMachine(lexisMachine.getOut())*/
    {
        in = _in;
        lexisMachine = LexisMachine(in);
    }

	TQueue<Lexem> getValidatedOut()
	{
		validate();
		if (errors.isEmpty())
		{
			postfixConverter = PostfixConverter(syntaxisMachine.getOut());
			postfixConverter.convert();
			return postfixConverter.getOut();
		}
		else
		{
			cout << errors << endl;
			throw - 1;
		}

	}

};