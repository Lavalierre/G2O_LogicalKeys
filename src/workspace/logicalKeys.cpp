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

SQFUNC(bindLogicalKey)
{
	int iArgs = SqModule::api->gettop(vm) - 1;
	if (iArgs < 2 && iArgs > 3)
		return SqModule::api->throwerror(vm, "(bindLogicalKey) wrong number of parameters, expecting 2");

	if (SqModule::api->gettype(vm, 2) != OT_INTEGER)
		return SqModule::api->throwerror(vm, "(bindLogicalKey) wrong type of parameter 1, expecting 'integer'");
	if (SqModule::api->gettype(vm, 3) != OT_INTEGER)
		return SqModule::api->throwerror(vm, "(bindLogicalKey) wrong type of parameter 2, expecting 'integer'");

	SQInteger logicalKey;
	SQInteger gameKey = 0;
	SQInteger addGameKey = 0;

	SqModule::api->getinteger(vm, 2, &logicalKey);
	SqModule::api->getinteger(vm, 3, &gameKey);

	if (SqModule::api->gettype(vm, 4) == OT_INTEGER)
		SqModule::api->getinteger(vm, 4, &addGameKey);

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

SQFUNC(unbindLogicalKey)
{
	int iArgs = SqModule::api->gettop(vm) - 1;
	if (iArgs != 1)
		return SqModule::api->throwerror(vm, "(unbindLogicalKey) wrong number of parameters, expecting 1");

	if (SqModule::api->gettype(vm, -1) != OT_INTEGER)
		return SqModule::api->throwerror(vm, "(unbindLogicalKey) wrong type of parameter 1, expecting 'integer'");

	SQInteger logicalKey;
	SqModule::api->getinteger(vm, -1, &logicalKey);

	if ((int)logicalKey >= GAME_UP && (int)logicalKey <= GAME_LAME_HEAL)
	{
		zWORD buffer = 0x0000;
		zoptions->WriteRaw("KEYS", getConfigKeyByLogical((int)logicalKey).c_str(), &buffer, sizeof(buffer), FALSE);
		zinput->BindKeys(0);
		return 1;
	}

	return 0;
}

SQFUNC(defaultLogicalKeys)
{
	int iArgs = SqModule::api->gettop(vm) - 1;
	if (iArgs != 1)
		return SqModule::api->throwerror(vm, "(defaultLogicalKeys) wrong number of parameters, expecting 1");

	if (SqModule::api->gettype(vm, -1) != OT_BOOL)
		return SqModule::api->throwerror(vm, "(defaultLogicalKeys) wrong type of parameter 1, expecting 'bool'");

	SQBool alternative;
	SqModule::api->getbool(vm, -1, &alternative);

	for (auto it = m_OPT_KEY_MAP.begin(); it != m_OPT_KEY_MAP.end(); it++)
		zoptions->RemoveEntry("KEYS", it->first.c_str());

	zinput->BindKeys(alternative);
}

SQFUNC(getLogicalKey)
{
	int iArgs = SqModule::api->gettop(vm) - 1;
	if (iArgs != 1)
		return SqModule::api->throwerror(vm, "() wrong number of parameters, expecting 1");

	if (SqModule::api->gettype(vm, -1) != OT_INTEGER)
		return SqModule::api->throwerror(vm, "(unbindLogicalKey) wrong type of parameter 1, expecting 'integer'");

	SQInteger logicalKey;
	SqModule::api->getinteger(vm, -1, &logicalKey);

	if ((int)logicalKey >= GAME_UP && (int)logicalKey <= GAME_LAME_HEAL)
	{
		zCArray<zWORD> controlValues;
		controlValues.EmptyList();
		zinput->GetBinding(logicalKey, controlValues);

		SqModule::api->newarray(vm, 0);
		for (int i = 0; i < controlValues.GetNumInList(); i++)
		{
			SqModule::api->pushinteger(vm, controlValues[i]);
			SqModule::api->arrayappend(vm, -2);
		}

		return 1;
	}

	return 0;
}

void InitLogicalKeys()
{
	HSQUIRRELVM vm = SqModule::vm;

	// Registering logical keys as global Squirrel constants
	SqRegisterValue(vm, "GAME_LEFT",			GAME_LEFT);
	SqRegisterValue(vm, "GAME_RIGHT",			GAME_RIGHT);
	SqRegisterValue(vm, "GAME_UP",				GAME_UP);
	SqRegisterValue(vm, "GAME_DOWN",			GAME_DOWN);
	SqRegisterValue(vm, "GAME_ACTION",			GAME_ACTION);
	SqRegisterValue(vm, "GAME_SLOW",			GAME_SLOW);
	SqRegisterValue(vm, "GAME_ACTION2",			GAME_ACTION2);
	SqRegisterValue(vm, "GAME_WEAPON",			GAME_WEAPON);
	SqRegisterValue(vm, "GAME_SMOVE",			GAME_SMOVE);
	SqRegisterValue(vm, "GAME_SMOVE2",			GAME_SMOVE2);
	SqRegisterValue(vm, "GAME_SHIFT",			GAME_SHIFT);
	SqRegisterValue(vm, "GAME_END",				GAME_END);
	SqRegisterValue(vm, "GAME_INVENTORY",		GAME_INVENTORY);
	SqRegisterValue(vm, "GAME_LOOK",			GAME_LOOK);
	SqRegisterValue(vm, "GAME_SNEAK",			GAME_SNEAK);
	SqRegisterValue(vm, "GAME_STRAFELEFT",		GAME_STRAFELEFT);
	SqRegisterValue(vm, "GAME_STRAFERIGHT",		GAME_STRAFERIGHT);
	SqRegisterValue(vm, "GAME_SCREEN_STATUS",	GAME_SCREEN_STATUS);
	SqRegisterValue(vm, "GAME_SCREEN_LOG",		GAME_SCREEN_LOG);
	SqRegisterValue(vm, "GAME_SCREEN_MAP",		GAME_SCREEN_MAP);
	SqRegisterValue(vm, "GAME_LOOK_FP",			GAME_LOOK_FP);
	SqRegisterValue(vm, "GAME_LOCK_TARGET",		GAME_LOCK_TARGET);
	SqRegisterValue(vm, "GAME_PARADE",			GAME_PARADE);
	SqRegisterValue(vm, "GAME_ACTIONLEFT",		GAME_ACTIONLEFT);
	SqRegisterValue(vm, "GAME_ACTIONRIGHT",		GAME_ACTIONRIGHT);
	SqRegisterValue(vm, "GAME_LAME_POTION",		GAME_LAME_POTION);
	SqRegisterValue(vm, "GAME_LAME_HEAL",		GAME_LAME_HEAL);

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
	SqRegisterFunction(vm, "bindLogicalKey",		bindLogicalKey);
	SqRegisterFunction(vm, "unbindLogicalKey",		unbindLogicalKey);
	SqRegisterFunction(vm, "defaultLogicalKeys",	defaultLogicalKeys);
	SqRegisterFunction(vm, "getLogicalKey",			getLogicalKey);
}