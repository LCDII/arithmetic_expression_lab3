#include"Handler.h"
#include"Exceptions.h"

Handler::Handler() :next(nullptr){}
Handler::~Handler()
{
	if (next != nullptr)
		delete next;
}
Handler::Handler(const Handler& handler)
{
	next = handler.next;
}
Handler::Handler(Handler* _next) : next(_next) {}
void Handler::run(ISolver* solver)
{
	if (next != nullptr)
		next->run(solver);
	else
		throw NoNextHandlersException("Обработчики в цепочке закончились");
}
void Handler::add(Handler* _next)
{
	next = _next;
}