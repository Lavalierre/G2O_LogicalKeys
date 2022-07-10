#include "callFunction.h"

using namespace SqModule;

static SQInteger stackSize;

bool SqModule::initCallFunction(const SQChar* name)
{
	api->pushroottable(vm);
	api->pushstring(vm, name, -1);

	if (SQ_SUCCEEDED(api->get(vm, -2)))
	{
		stackSize = api->gettop(vm);
		api->pushroottable(vm);

		return true;
	}

	return false;
}

void SqModule::callFunction(bool ret)
{
	api->call(vm, api->gettop(vm) - stackSize, SQBool(ret), SQTrue);

	if (!ret)
		api->pop(vm, 2);
	else
	{
		api->remove(vm, -2);
		api->remove(vm, -2);
	}
}
