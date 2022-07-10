#include "pch.h"
#include "logicalKeys.h"

std::map <std::string, int> m_OPT_KEY_MAP;									// Storage of config keys

std::string getConfigKeyByLogical(int logicalKey)
{
	for (auto it = m_OPT_KEY_MAP.begin(); it != m_OPT_KEY_MAP.end(); it++)
	{
		if (it->second == logicalKey)
			return it->first;
	}

	return "";
}

int getLogicalKeyByConfig(std::string configKey)
{
	for (auto it = m_OPT_KEY_MAP.begin(); it != m_OPT_KEY_MAP.end(); it++)
	{
		if (it->first == configKey)
			return it->second;
	}

	return -1;
}

void RegisterLogicalKey(std::string keyName, std::string configKey, int gameKey)
{
	Sqrat::ConstTable().Const(keyName.c_str(), gameKey);					// Registering logical key as global variable
	m_OPT_KEY_MAP.insert(std::pair<std::string, int>(configKey, gameKey));	// Binding config key to logical key
}

//--------------------------------------------------------------------------------

SQInteger bindLogicalKey(HSQUIRRELVM vm)
{
	SQInteger top = sq_gettop(vm);
	if (top > 4)
		return sq_throwerror(vm, "wrong number of parameters");

	SQInteger logicalKey	= 0;
	SQInteger gameKey		= 0;
	SQInteger addGameKey	= 0;

	sq_getinteger(vm, 2, &logicalKey);
	sq_getinteger(vm, 3, &gameKey);

	if (top == 4)
		sq_getinteger(vm, 4, &addGameKey);

	if (logicalKey >= GAME_UP && logicalKey <= GAME_LAME_HEAL)
	{
		std::string configKey = getConfigKeyByLogical(logicalKey);
		if (configKey != "")
		{
			zCArray<zWORD> controlValueList;
			controlValueList.EmptyList();

			controlValueList.Insert(gameKey);

			if (addGameKey != 0)
				controlValueList.Insert(addGameKey);

			zoptions->WriteRaw("KEYS", configKey.c_str(), controlValueList.GetArray(), controlValueList.GetNumInList() << 1, FALSE);
			zinput->BindKeys(0);
		}
    
		return 1;
	}

	sq_pushbool(vm, FALSE);
	return 0;
}

SQInteger unbindLogicalKey(HSQUIRRELVM vm)
{
	SQInteger logicalKey;
	sq_getinteger(vm, 2, &logicalKey);

	if (logicalKey >= GAME_UP && logicalKey <= GAME_LAME_HEAL)
	{
		std::string configKey = getConfigKeyByLogical(logicalKey);
		if (configKey != "")
		{
			zWORD buffer = 0x0000;
			zoptions->WriteRaw("KEYS", configKey.c_str(), &buffer, sizeof(buffer), FALSE);
			zinput->BindKeys(0);
		}
		return 1;
	}

	sq_pushbool(vm, FALSE);
	return 0;
}

SQInteger defaultLogicalKeys(HSQUIRRELVM vm)
{
	SQBool alternative;
	sq_getbool(vm, -1, &alternative);

	for (auto it = m_OPT_KEY_MAP.begin(); it != m_OPT_KEY_MAP.end(); it++)
		zoptions->RemoveEntry("KEYS", it->first.c_str());
	
	zinput->BindKeys(alternative);

	return 1;
}

SQInteger getLogicalKey(HSQUIRRELVM vm)
{
	SQInteger logicalKey;
	sq_getinteger(vm, 2, &logicalKey);

	if (logicalKey >= GAME_UP && logicalKey <= GAME_LAME_HEAL)
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

	sq_pushnull(vm);
	return 0;
}

void InitLogicalKeys(Sqrat::RootTable roottable)
{
	using namespace SqModule;

	// Registering logical keys for config and squirrel constants
	RegisterLogicalKey("GAME_LAME_HEAL",		"keyHeal",			GAME_LAME_HEAL);			// Heal potion hotkey
	RegisterLogicalKey("GAME_LAME_POTION",		"keyPotion",		GAME_LAME_POTION);			// Mana potion hotkey

	RegisterLogicalKey("GAME_LOCK_TARGET",		"keyLockTarget",	GAME_LOCK_TARGET);
	RegisterLogicalKey("GAME_LOOK",				"keyLook",			GAME_LOOK);
	RegisterLogicalKey("GAME_LOOK_FP",			"keyLookFP",		GAME_LOOK_FP);				// Firstperson mode hotkey

	RegisterLogicalKey("GAME_PARADE",			"keyParade",		GAME_PARADE);
	RegisterLogicalKey("GAME_WEAPON",			"keyWeapon",		GAME_WEAPON);

	RegisterLogicalKey("GAME_ACTIONRIGHT",		"keyActionRight",	GAME_ACTIONRIGHT);			// G2 controls stuff
	RegisterLogicalKey("GAME_ACTIONLEFT",		"keyActionLeft",	GAME_ACTIONLEFT);			// G2 controls stuff
	RegisterLogicalKey("GAME_ACTION",			"keyAction",		GAME_ACTION);

	RegisterLogicalKey("GAME_UP",				"keyUp",			GAME_UP);
	RegisterLogicalKey("GAME_DOWN",				"keyDown",			GAME_DOWN);
	RegisterLogicalKey("GAME_RIGHT",			"keyRight",			GAME_RIGHT);
	RegisterLogicalKey("GAME_LEFT",				"keyLeft",			GAME_LEFT);

	RegisterLogicalKey("GAME_STRAFELEFT",		"keyStrafeLeft",	GAME_STRAFELEFT);
	RegisterLogicalKey("GAME_STRAFERIGHT",		"keyStrafeRight",	GAME_STRAFERIGHT);

	RegisterLogicalKey("GAME_SLOW",				"keySlow",			GAME_SLOW);					// Walk mode
	RegisterLogicalKey("GAME_SMOVE",			"keySMove",			GAME_SMOVE);				// Special Move / Jump
	RegisterLogicalKey("GAME_SNEAK",			"keySneak",			GAME_SNEAK);

	RegisterLogicalKey("GAME_INVENTORY",		"keyInventory",		GAME_INVENTORY);
	RegisterLogicalKey("GAME_SCREEN_STATUS",	"keyShowStatus",	GAME_SCREEN_STATUS);
	RegisterLogicalKey("GAME_SCREEN_LOG",		"keyShowLog",		GAME_SCREEN_LOG);
	RegisterLogicalKey("GAME_SCREEN_MAP",		"keyShowMap",		GAME_SCREEN_MAP);
	RegisterLogicalKey("GAME_END",				"keyEnd",			GAME_END);

	// Registering squirrel functions
	roottable.SquirrelFunc("bindLogicalKey",		bindLogicalKey,			-3,		".iii");
	roottable.SquirrelFunc("unbindLogicalKey",		unbindLogicalKey,		2,		".i");
	roottable.SquirrelFunc("defaultLogicalKeys",	defaultLogicalKeys,		2,		".b");
	roottable.SquirrelFunc("getLogicalKey",			getLogicalKey,			2,		".i");
}