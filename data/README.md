## LUA API
List of possible method calls in LUA scripts.

***

### Functions

 | METHOD | DESCRIPTION |
 | :----: | ----------- |
 | `Fn.wait(FRAMES)` | Waits for FRAMES amount of frames |
 | | |
 | `UNIT:getPos()` | Returns position of UNIT as two variables x, y |
 | `UNIT:offset(x, y)` | Offsets UNIT by x and y pixels |
 | `UNIT:resetOffset()` | Resets offset of UNIT *(Makes unit align with its tile)* |
 | `UNIT:getItem()` | Returns table of first item in UNIT inventory or nil if inventory is empty |
 | `UNIT:getPhysical()` | Returns physical stats of UNIT *(STR, DEF and AGI)* |
 | `UNIT:getHP()` | Returns HP of UNIT  |
 | `UNIT:damage(x)` | Deals x amount of damage to HP of UNIT |
