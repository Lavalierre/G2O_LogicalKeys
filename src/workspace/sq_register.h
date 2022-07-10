#pragma once

void SqRegisterFunction(HSQUIRRELVM vm, const char* name, SQFUNCTION func);
void SqRegisterValue(HSQUIRRELVM vm, const char* name, int value);
