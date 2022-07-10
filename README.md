# About
 Simple client-side module, that allows you manipulate with game's logical keys (for example, rebind character controls).
 
 # Usage
 
## New logical key IDs as global constants
```
GAME_LEFT
GAME_RIGHT
GAME_UP
GAME_DOWN
GAME_ACTION
GAME_SLOW
GAME_ACTION2
GAME_WEAPON
GAME_SMOVE
GAME_SMOVE2
GAME_SHIFT
GAME_END
GAME_INVENTORY
GAME_LOOK
GAME_SNEAK
GAME_STRAFELEFT
GAME_STRAFERIGHT
GAME_SCREEN_STATUS
GAME_SCREEN_LOG
GAME_SCREEN_MAP
GAME_LOOK_FP
GAME_LOCK_TARGET
GAME_PARADE
GAME_ACTIONLEFT
GAME_ACTIONRIGHT
GAME_LAME_POTION
GAME_LAME_HEAL
```
## New functions
``void bingLogicalKey(int logicalKeyID, int keyID, [int additionalKeyID])`` - rebinds the logical key with new given physical keys. ``additionalKeyID`` is optional.

``void unbindLogicalKey(int logicalKeyID)`` - unbind all physical keys from the logical key.

``array[] getLogicalKey(int logicalKeyID)`` - get all binded physical keys to the given logical key.

``void defaultLogicalKeys(bool alternative)`` - reset all the key binds to default settings. ``alternative`` arguments specifies which layout will be taken as default - default or alternative.

## Examples
```C++
addEventHandler("onCommand", function(cmd, params)
{

 if (cmd == "slow_move")
 {
  bindLogicalKey(GAME_SLOW, KEY_H); // binds key H to slow walk. Default slow walk is LSHIFT
 }
 
 if (cmd == "forward")
 {
  bindLogicalKey(GAME_UP, KEY_W, KEY_Z); // binds keys W and Z to GAME_UP key a.k.a. moving forward
 }
 
 if (cmd == "stop")
 {
  unbindLogicalKey(GAME_UP); // unbinds all keys from GAME_UP
 }
 
 if (cmd == "help")
 {
  // prints all binded physical keys to GAME_UP. Note, that it'll print key ids as numbers
  local controls = getLogicalKey(GAME_UP);
  for (local i = 0; i < controls.len(); i++)
   print("#" + i + " key for GAME_UP: " + controls[i]);
 }
 
 if (cmd == "reset")
 {
  defaultLogicalKeys(false); // reset all key binding to default settings
 }
});
```
