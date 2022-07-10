#ifndef _EVENT_H
#define _EVENT_H

#include "callFunction.h"
#include "pushArgs.h"

void addEvent(const char* eventName)
{
	using namespace SqModule;

	if (initCallFunction("addEvent"))
	{
		pushArg(eventName);
		callFunction(false);
	}
}

HSQOBJECT addEventHandler(const char* eventName, SQFUNCTION closure)
{
	using namespace SqModule;

	HSQOBJECT result;

	if (initCallFunction("addEventHandler"))
	{
		pushArg(eventName);
		api->newclosure(vm, closure, 0);

		// get closure handle
		api->resetobject(&result);
		api->getstackobj(vm, -1, &result);
		api->addref(vm, &result);

		callFunction(false);
	}

	return result;
}

HSQOBJECT addEventHandler(const char* eventName, SQFUNCTION closure, int priority)
{
	using namespace SqModule;

	HSQOBJECT result;

	if (initCallFunction("addEventHandler"))
	{
		pushArg(eventName);
		pushArg(priority);
		api->newclosure(vm, closure, 0);

		// get closure handle
		api->resetobject(&result);
		api->getstackobj(vm, -1, &result);
		api->addref(vm, &result);

		callFunction(false);
	}

	return result;
}

void removeEvent(const char* eventName)
{
	using namespace SqModule;

	if (initCallFunction("removeEvent"))
	{
		pushArg(eventName);
		callFunction(false);
	}
}

bool removeEventHandler(const char* eventName, HSQOBJECT closure)
{
	using namespace SqModule;

	SQBool result = false;

	if (initCallFunction("removeEventHandler"))
	{
		pushArg(eventName);
		api->pushobject(vm, closure);

		callFunction(true);

		api->getbool(vm, -1, &result);
		api->pop(vm, -1);
	}

	return result;
}

template <typename ...vargv >
bool callEvent(vargv... args)
{
	using namespace SqModule;

	SQBool cancelled = false;

	if (initCallFunction("callEvent"))
	{
		pushArgs(args...);
		callFunction(true);

		api->getbool(vm, -1, &cancelled);
		api->pop(vm, -1);
	}

	return cancelled
}

void cancelEvent()
{
	using namespace SqModule;

	if (initCallFunction("cancelEvent"))
		callFunction(false);
}

bool isEventCancelled()
{
	using namespace SqModule;

	SQBool cancelled = false;

	if (initCallFunction("isEventCancelled"))
	{
		callFunction(true);

		api->getbool(vm, -1, &cancelled);
		api->pop(vm, -1);
	}

	return cancelled;
}

void eventValue(int value)
{
	using namespace SqModule;

	if (initCallFunction("eventValue"))
	{
		pushArg(value);
		callFunction(false);
	}
}

#endif
