#ifndef _TIMER_H
#define _TIMER_H

#include "callFunction.h"
#include "pushArgs.h"

template <typename ...vargv >
int setTimer(SQFUNCTION callback, int time, int repeatTimes, vargv... args)
{
	using namespace SqModule;

	SQInteger timerId = -1;

	if (initCallFunction("setTimer"))
	{
		api->newclosure(vm, callback, 0);
		pushArg(time);
		pushArg(repeatTimes);
		pushArgs(args...);

		callFunction(true);

		api->getinteger(vm, -1, &timerId);
		api->pop(vm, -1);
	}	

	return timerId;
}

void killTimer(int id)
{
	using namespace SqModule;

	if (initCallFunction("killTimer"))
	{
		pushArg(id);
		callFunction(false);
	}
}

void setTimerInterval(int id, int interval)
{
	using namespace SqModule;

	if (initCallFunction("setTimerInterval"))
	{
		pushArg(id);
		pushArg(interval);

		callFunction(false);
	}
}

int getTimerInterval(int id)
{
	using namespace SqModule;

	SQInteger interval = -1;

	if (initCallFunction("getTimerInterval"))
	{
		pushArg(id);
		callFunction(true);

		api->getinteger(vm, -1, &interval);
		api->pop(vm, -1);
	}

	return interval;
}

void setTimerExecuteTimes(int id, int times)
{
	using namespace SqModule;

	if (initCallFunction("setTimerExecuteTimes"))
	{
		pushArg(id);
		pushArg(times);

		callFunction(false);
	}
}

int getTimerExecuteTimes(int id)
{
	using namespace SqModule;

	SQInteger executeTimes;

	if (initCallFunction("getTimerExecuteTimes"))
	{
		pushArg(id);
		callFunction(true);

		api->getinteger(vm, -1, &executeTimes);
		api->pop(vm, -1);
	}

	return executeTimes;
}

#endif