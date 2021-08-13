## LUA API
List of possible method calls in LUA scripts.

***

### Functions

 | METHOD | DESCRIPTION |
 | :----: | ----------- |
 | `Fn.wait(FRAMES)` | Waits for FRAMES amount of frames |
 | | |
 | `Unit.getPos(UNIT)` | Returns position of UNIT as two variables x, y |
 | `Unit.offset(UNIT, x, y)` | Offsets UNIT by x and y pixels |
 | `Unit.resetOffset(UNIT)` | Resets offset of UNIT *(Makes unit align with its tile)* |
 | `Unit.getItem(UNIT)` | Returns table of first item in UNIT inventory or nil if inventory is empty |
 | `Unit.getPhysical(UNIT)` | Returns physical stats of UNIT *(STR and DEF)* |
 | `Unit.getHP(UNIT)` | Returns HP of UNIT  |
 | `Unit.damage(UNIT, x)` | Deals x amount of damage to HP of UNIT |
