#include "pch.h"
#include "logicalKeys.h"

std::map <std::string, int> m_OPT_KEY_MAP;

void AddOptKeyValue(std::string key, int value)
{
	m_OPT_KEY_MAP.insert(std::pair<std::string, int>(key, value));
}

std::string getConfigKeyByLogical(int logicalKey)
{
	for (auto it = m_OPT_KEY_MAP.begin(); it != m_OPT_KEY_MAP.end(); it++)
	{
		if (it->second == logicalKey)
			return it->first;
	}
}

int getLogicalKeyByConfig(std::string configKey)
{
	for (auto it = m_OPT_KEY_MAP.begin(); it != m_OPT_KEY_MAP.end(); it++)
	{
		if (it->first == configKey)
			return it->second;
	}
}

//--------------------------------------------------------------------------------

SQInteger bindLogicalKey(HSQUIRRELVM vm)
{
	int iArgs = sq_gettop(vm) - 1;
	if (iArgs < 2 && iArgs > 3)
		return sq_throwerror(vm, "(bindLogicalKey) wrong number of parameters, expecting 2");

	if (sq_gettype(vm, 2) != OT_INTEGER)
		return sq_throwerror(vm, "(bindLogicalKey) wrong type of parameter 1, expecting 'integer'");
	if (sq_gettype(vm, 3) != OT_INTEGER)
		return sq_throwerror(vm, "(bindLogicalKey) wrong type of parameter 2, expecting 'integer'");

	SQInteger logicalKey;
	SQInteger gameKey = 0;
	SQInteger addGameKey = 0;

	sq_getinteger(vm, 2, &logicalKey);
	sq_getinteger(vm, 3, &gameKey);

	if (sq_gettype(vm, 4) == OT_INTEGER)
		sq_getinteger(vm, 4, &addGameKey);

	if ((int)logicalKey >= GAME_UP && (int)logicalKey <= GAME_LAME_HEAL)
	{
		zCArray<zWORD> controlValueList;
		controlValueList.EmptyList();

		if (logicalKey != 0)
			controlValueList.Insert(gameKey);
		if (addGameKey != 0)
			controlValueList.Insert(addGameKey);

		zoptions->WriteRaw("KEYS", getConfigKeyByLogical((int)logicalKey).c_str(), controlValueList.GetArray(), controlValueList.GetNumInList() << 1, FALSE);
		zinput->BindKeys(0);
		return 1;
	}

	return 0;
}

SQInteger unbindLogicalKey(HSQUIRRELVM vm)
{
	int iArgs = sq_gettop(vm) - 1;
	if (iArgs != 1)
		return sq_throwerror(vm, "(unbindLogicalKey) wrong number of parameters, expecting 1");

	if (sq_gettype(vm, -1) != OT_INTEGER)
		return sq_throwerror(vm, "(unbindLogicalKey) wrong type of parameter 1, expecting 'integer'");

	SQInteger logicalKey;
	sq_getinteger(vm, -1, &logicalKey);

	if ((int)logicalKey >= GAME_UP && (int)logicalKey <= GAME_LAME_HEAL)
	{
		zWORD buffer = 0x0000;
		zoptions->WriteRaw("KEYS", getConfigKeyByLogical((int)logicalKey).c_str(), &buffer, sizeof(buffer), FALSE);
		zinput->BindKeys(0);
		return 1;
	}

	return 0;
}

SQInteger defaultLogicalKeys(HSQUIRRELVM vm)
{
	int iArgs = sq_gettop(vm) - 1;
	if (iArgs != 1)
		return sq_throwerror(vm, "(defaultLogicalKeys) wrong number of parameters, expecting 1");

	if (sq_gettype(vm, -1) != OT_BOOL)
		return sq_throwerror(vm, "(defaultLogicalKeys) wrong type of parameter 1, expecting 'bool'");

	SQBool alternative;
	sq_getbool(vm, -1, &alternative);

	for (auto it = m_OPT_KEY_MAP.begin(); it != m_OPT_KEY_MAP.end(); it++)
		zoptions->RemoveEntry("KEYS", it->first.c_str());

	zinput->BindKeys(alternative);
}

SQInteger getLogicalKey(HSQUIRRELVM vm)
{
	int iArgs = sq_gettop(vm) - 1;
	if (iArgs != 1)
		return sq_throwerror(vm, "(getLogicalKey) wrong number of parameters, expecting 1");

	if (sq_gettype(vm, -1) != OT_INTEGER)
		return sq_throwerror(vm, "(getLogicalKey) wrong type of parameter 1, expecting 'integer'");

	SQInteger logicalKey;
	sq_getinteger(vm, -1, &logicalKey);

	if ((int)logicalKey >= GAME_UP && (int)logicalKey <= GAME_LAME_HEAL)
	{
		zCArray<zWORD> controlValues;
		controlValues.EmptyList();
		zinput->GetBinding(logicalKey, controlValues);

		sq_newarray(vm, 0);
		for (int i = 0; i < controlValues.GetNumInList(); i++)
		{
			sq_pushinteger(vm, controlValues[i]);
			sq_arrayappend(vm, -2);
		}

		return 1;
	}

	return 0;
}

void InitLogicalKeys()
{
	using namespace SqModule;

	Sqrat::RootTable roottable(vm);
	Sqrat::ConstTable consttable(vm);

	// Registering logical keys as global Squirrel constants
	consttable.Const("GAME_LEFT",				GAME_LEFT);
	consttable.Const("GAME_RIGHT",				GAME_RIGHT);
	consttable.Const("GAME_UP",					GAME_UP);
	consttable.Const("GAME_DOWN",				GAME_DOWN);
	consttable.Const("GAME_ACTION",				GAME_ACTION);
	consttable.Const("GAME_SLOW",				GAME_SLOW);
	consttable.Const("GAME_ACTION2",			GAME_ACTION2);
	consttable.Const("GAME_WEAPON",				GAME_WEAPON);
	consttable.Const("GAME_SMOVE",				GAME_SMOVE);
	consttable.Const("GAME_SMOVE2",				GAME_SMOVE2);
	consttable.Const("GAME_SHIFT",				GAME_SHIFT);
	consttable.Const("GAME_END",				GAME_END);
	consttable.Const("GAME_INVENTORY",			GAME_INVENTORY);
	consttable.Const("GAME_LOOK",				GAME_LOOK);
	consttable.Const("GAME_SNEAK",				GAME_SNEAK);
	consttable.Const("GAME_STRAFELEFT",			GAME_STRAFELEFT);
	consttable.Const("GAME_STRAFERIGHT",		GAME_STRAFERIGHT);
	consttable.Const("GAME_SCREEN_STATUS",		GAME_SCREEN_STATUS);
	consttable.Const("GAME_SCREEN_LOG",			GAME_SCREEN_LOG);
	consttable.Const("GAME_SCREEN_MAP",			GAME_SCREEN_MAP);
	consttable.Const("GAME_LOOK_FP",			GAME_LOOK_FP);
	consttable.Const("GAME_LOCK_TARGET",		GAME_LOCK_TARGET);
	consttable.Const("GAME_PARADE",				GAME_PARADE);
	consttable.Const("GAME_ACTIONLEFT",			GAME_ACTIONLEFT);
	consttable.Const("GAME_ACTIONRIGHT",		GAME_ACTIONRIGHT);
	consttable.Const("GAME_LAME_POTION",		GAME_LAME_POTION);
	consttable.Const("GAME_LAME_HEAL",			GAME_LAME_HEAL);

	// Map for Gothic.ini controls section
	AddOptKeyValue("keyEnd",					GAME_END);
	AddOptKeyValue("keyHeal",					GAME_LAME_HEAL);
	AddOptKeyValue("keyPotion",					GAME_LAME_POTION);
	AddOptKeyValue("keyLockTaget",				GAME_LOCK_TARGET);
	AddOptKeyValue("keyParade",					GAME_PARADE);
	AddOptKeyValue("keyActionRight",			GAME_ACTIONRIGHT);
	AddOptKeyValue("keyActionLeft",				GAME_ACTIONLEFT);
	AddOptKeyValue("keyUp",						GAME_UP);
	AddOptKeyValue("keyDown",					GAME_DOWN);
	AddOptKeyValue("keyLeft",					GAME_LEFT);
	AddOptKeyValue("keyRight",					GAME_RIGHT);
	AddOptKeyValue("keyStrafeLeft",				GAME_STRAFELEFT);
	AddOptKeyValue("keyStrafeRight",			GAME_STRAFERIGHT);
	AddOptKeyValue("keyAction",					GAME_ACTION);
	AddOptKeyValue("keySlow",					GAME_SLOW);
	AddOptKeyValue("keySMove",					GAME_SMOVE);
	AddOptKeyValue("keyWeapon",					GAME_WEAPON);
	AddOptKeyValue("keySneak",					GAME_SNEAK);
	AddOptKeyValue("keyLook",					GAME_LOOK);
	AddOptKeyValue("keyLookFP",					GAME_LOOK_FP);
	AddOptKeyValue("keyInventory",				GAME_INVENTORY);
	AddOptKeyValue("keyShowStatus",				GAME_SCREEN_STATUS);
	AddOptKeyValue("keyShowLog",				GAME_SCREEN_LOG);
	AddOptKeyValue("keyShowMap",				GAME_SCREEN_MAP);

	// Registering squirrel functions
	roottable.SquirrelFunc("bindLogicalKey",	bindLogicalKey);
	roottable.SquirrelFunc("unbindLogicalKey",	unbindLogicalKey);
	roottable.SquirrelFunc("defaultLogicalKeys",defaultLogicalKeys);
	roottable.SquirrelFunc("getLogicalKey",		getLogicalKey);
}