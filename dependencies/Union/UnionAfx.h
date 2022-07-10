// Supported with union (c) 2018-2021 Union team

#ifndef __UNION_AFX_H__
#define __UNION_AFX_H__

extern "C" {
  #include <Windows.h>
  #include <stdlib.h>
  #include <stdio.h>
  #include <math.h>
  #include <Psapi.h>
  #include <time.h>
}

#pragma warning(disable:4005)
#pragma warning(disable:4244)
#pragma warning(disable:4731)

#include "Union/Macro.h"
#define CStringA zSTRING

#include "Union/Types.h"
using namespace Common;

#include "Union/CUntyped.h"
using namespace UnionCore;

// gothic engine classes for g1, g1a, g2 and g2a
#include "ZenGin/zGothicAPI.h"

#pragma warning(default:4005)
#pragma warning(default:4244)
#pragma warning(default:4731)

#endif // __UNION_AFX_H__