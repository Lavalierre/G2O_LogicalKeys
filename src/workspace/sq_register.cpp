#include "pch.h"

void SqRegisterFunction(HSQUIRRELVM vm, const char* name, SQFUNCTION func)
{
	sq_pushroottable(vm);
	sq_pushstring(vm, name, -1);
	sq_newclosure(vm, func, 0);
	sq_newslot(vm, -3, SQFalse);
	sq_pop(vm, 1);
}

void SqRegisterValue(HSQUIRRELVM vm, const char* name, int value)
{
	sq_pushroottable(vm);
	sq_pushstring(vm, name, -1);
	sq_pushinteger(vm, value);
	sq_newslot(vm, -3, SQFalse);
	sq_pop(vm, 1);
}