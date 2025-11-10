
#include"LexisMachine.h"
#include"SyntaxisMachine.h"
#include"Validator.h"
#include"ArithmeticExpression.h"

int main()
{
	string s = "(40*(-15+30)/15)-1";
	/*LexisMachine lexm(s);
	lexm.validate();
	TQueue<Lexem>_(lexm.getOut());
	while (!_.isEmpty())
	{
		cout << _.pop();
	}
	cout << endl;

	SyntaxisMachine synt(lexm.getOut());
	synt.validate();

	cout << "ERRORS IN INDEXES: " << endl;
	cout << synt.getErrors();
	cout << endl << endl << endl;*/
	
	Validator* validator = new Validator(s);

	ArithmeticExpression ae(s);
	ae.setValidator(validator);
	ae.validate();
	
	cout << endl;
	TQueue<Lexem>_(ae.getOut());
	while (!_.isEmpty())
	{
		cout << _.pop();
	}
	cout << endl;
}