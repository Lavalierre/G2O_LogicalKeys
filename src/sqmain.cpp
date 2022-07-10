#include "pch.h"
#include "workspace/logicalKeys.h"

extern "C" SQRESULT SQRAT_API sqmodule_load(HSQUIRRELVM vm, HSQAPI api)
{
	SqModule::Initialize(vm, api);
	Sqrat::DefaultVM::Set(vm);

	Sqrat::RootTable roottable(vm);

	InitLogicalKeys(roottable);

	return SQ_OK;
}