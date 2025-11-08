#pragma once


class IFinalStateMachine
{

protected:
	int** next;
	int state;
public:
	IFinalStateMachine(): state(0){}
	virtual void validate()
	{
		cout << "Done";
	}
};