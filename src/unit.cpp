#include "unit.hpp"
#include "globals.hpp"
#include "asset_manager.hpp"

// Create new unit
auto cUnit::newUnit(const std::string& p_className, 
	eTEAM_COLOR p_color, cBattleLua &Lua) -> cUnit* {
	cUnit* unit = new cUnit;

	auto failure = [&unit](){
		delete unit;
		return nullptr;
	};
	
	// Find unit table
	lua_getglobal(Lua(), p_className.c_str());
	if(not lua_istable(Lua(), -1)) {
		std::cout << "[ERROR] No class with name " << p_className << std::endl;
		return failure();
	}

	// Get field
	auto getStat = [&Lua, &p_className](const std::string& field, uint8_t &stat) {
		lua_getfield(Lua(), -1, field.c_str());
		if(not lua_isinteger(Lua(), -1)) {
			std::cout << "[ERROR] No " << field << " for " << p_className << std::endl; 
			return 0;
		}
		stat = (uint8_t)lua_tointeger(Lua(), -1);
		lua_pop(Lua(), 1);
		return 1;
	};

	// Get unit stats
	auto &stats = unit->m_stats;
	if(not getStat("hp", stats.HP)) return failure();
	if(not getStat("mp", stats.MP)) return failure();
	if(not getStat("def", stats.DEF)) return failure();
	if(not getStat("str", stats.STR)) return failure();
	if(not getStat("agi", stats.AGI)) return failure();
	if(not getStat("int", stats.INT)) return failure();
	if(not getStat("mov", stats.MOV)) return failure();

	// Get useable items
	lua_getfield(Lua(), -1, "use");
	if(not lua_istable(Lua(), -1)) {
		std::cout << "[ERROR] No use table for " << p_className << std::endl;
		return failure();
	}
	lua_pushnil(Lua());		// Push key
	while(lua_next(Lua(), -2) != 0) {
		// Convert to useable flag
		if(lua_isinteger(Lua(), -1)) {
			unit->m_useableItems |= (uint8_t)lua_tointeger(Lua(), -1);
		}
		else {
			std::cout << "[WARN] Unrecognized use flag in " << p_className << std::endl;
		}
		lua_pop(Lua(), 1);
	}
	lua_pop(Lua(), 1);

	// Get starting gear
	std::vector<std::string> items(5);
	lua_getfield(Lua(), -1, "gear");
	if(not lua_istable(Lua(), -1)){
		std::cout << "[ERROR] No starting gear for " << p_className << std::endl;
	}
	else {
		lua_pushnil(Lua());		// Push key
		while(lua_next(Lua(), -2) != 0) {
			if(lua_isstring(Lua(), -1)) {
				items.push_back(lua_tostring(Lua(), -1));
			}
			else {
				std::cout << "[WARN] Unrecognized gear in " << p_className << std::endl;
			}
			lua_pop(Lua(), 1);
		}
		lua_pop(Lua(), 1);
	}

	// Add items
	for(auto& itemID : items) {
		auto item = cItem::newItem(itemID, Lua);
		if(item.getID() != "") unit->inventory().addNewItem(item);
	}

	// Set name
	unit->m_name = p_className;
	for(auto& c: unit->m_name) c = tolower(c);
	std::cout << "Unit name " << unit->m_name << std::endl;

	// Get sprite
	auto assets = cAssetManager::getInstance();
	std::string spriteName;
	switch(p_color) {
		case eTEAM_COLOR::BLUE:
			spriteName = "unit_" + unit->m_name + "_blue";
			break;
		case eTEAM_COLOR::RED:
			spriteName = "unit_" + unit->m_name + "_red";
			break;
	}
	unit->m_sprite = assets.getSprite(unit->m_name, spriteName);

	return unit;
}

auto cUnit::getName() const -> const std::string& {
	return m_name;
}

// Set position on board
void cUnit::setPosition(vec2D p_pos){
	m_pos = p_pos;
}

// Offset position by given vector
void cUnit::offsetPosition(vec2D p_offset){
	m_offset.x += p_offset.x;
	m_offset.y += p_offset.y;
}

// Reset offset
void cUnit::resetOffset(){
	m_offset = {0, 0};
}

// Toggle active
void cUnit::toggleActive(bool p_active){
	m_active = p_active;
}

// Get unit stats
auto cUnit::getStats() -> const sStats&{
	return m_stats;
}

// Check if unit can use item
bool cUnit::canUse(uint8_t p_itemType){
	return (m_useableItems & p_itemType) == p_itemType; 
}

// Draw unit
void cUnit::draw(vec2D p_cameraOffset, int p_animationFrame){
	// Initialize drawing rectangles
	SDL_Rect srcRect{ 0 + TILE_SIZE * (p_animationFrame / 15)
			, 0
			, TILE_SIZE
			, TILE_SIZE
			};

	SDL_Rect dstRect{ m_pos.x * TILE_SIZE + m_offset.x + p_cameraOffset.x
			, m_pos.y * TILE_SIZE + m_offset.y + p_cameraOffset.y + RENDER_OFFSET
			, TILE_SIZE
			, TILE_SIZE
			};

	if(m_active) SDL_RenderCopy(g_renderer, m_sprite, &srcRect, &dstRect);
	else {
		SDL_SetTextureColorMod(m_sprite, 125, 125, 125);
		SDL_RenderCopy(g_renderer, m_sprite, &srcRect, &dstRect);
		SDL_SetTextureColorMod(m_sprite, 255, 255, 255);
	}
}

// Get position
auto cUnit::getPosition() -> vec2D{
	return m_pos;
}

// Get range
auto cUnit::range() -> cUnitRange&{
	return m_range;
}

// Get inventory
auto cUnit::inventory() -> cUnitInventory&{
	return m_inventory;
}
