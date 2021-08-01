## LUA API
List of possible method calls in LUA scripts.

***

### UNIT

 | METHOD | DESCRIPTION |
 | :----: | ----------- |
 | `Unit.getPos(UNIT)` | Returns position of UNIT as two LUA NUMBERS x and y |
 | `Unit.offset(UNIT, x, y)` | Offsets UNIT by x and y pixels |
 | `Unit.resetOffset(UNIT)` | Resets offset of UNIT *(Makes unit align with its tile)* |
 | `Unit.damage(UNIT, x)` | Deals x amount of damage to HP of UNIT |
