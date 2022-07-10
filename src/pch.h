#define QUOTIFY(arg) #arg
#define STRINGIFY(arg) QUOTIFY(arg)

#define SCRAT_EXPORT // Used to get SQRAT_API macro for sqmodule_load func (export function)
#define SQFUNC(x) SQInteger x(HSQUIRRELVM vm)

#include "api/module_api.h"
#include "api/squirrel_api.h"
#include "sqrat.h"

#include "UnionAfx.h"

#include "workspace/sq_register.h"

#define HOOK auto
#define AS = CreateHook