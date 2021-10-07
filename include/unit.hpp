#pragma once

#include "unit_range.hpp"
#include "unit_inventory.hpp"
#include "struct_vec2D.hpp"
#include "struct_stats.hpp"

#include "battle_lua.hpp"

#include <SDL2/SDL.h>

// Color of units
enum class eTEAM_COLOR{
	BLUE,
	RED
};

// Unit class
class cUnit{
	private:
		// Identification
		std::string m_name;

		cUnit() = default;

		// Position on map in tiles, offset in pixels
		vec2D m_pos{-1, -1};
		vec2D m_offset{0, 0};
		static constexpr int RENDER_OFFSET = -3;

		// Stats
		sStats m_stats;

		// Status
		bool m_active = true;

		// Bitmask of useable items by this unit
		uint8_t m_useableItems = 0;

		// Components ////////////////
		cUnitRange m_range = cUnitRange(*this);
		friend cUnitRange;
		
		cUnitInventory m_inventory = cUnitInventory(*this);
		friend cUnitInventory;

		//////////////////////////////

		// Sprite
		SDL_Texture* m_sprite;
	public:
		// Create new item by class name and 
		static auto newUnit(const std::string& p_className, 
			eTEAM_COLOR p_color, cBattleLua &Lua) -> cUnit*;

		auto getName() const -> const std::string&;

		// Methods for position
		void setPosition(vec2D p_pos);
		void offsetPosition(vec2D p_offset);
		void resetOffset();

		// Status methods
		void toggleActive(bool p_active);
		bool isActive(){ return m_active; };

		// Stats methods
		auto getStats() -> const sStats&;
		bool canUse(uint8_t p_itemType);
		void heal(int p_amount);

		// Drawing
		void draw(vec2D p_cameraOffset, int p_animationFrame);

		// Get position
		auto getPosition() -> vec2D;

		// Access components
		auto range()     -> cUnitRange&;
		auto inventory() -> cUnitInventory&;

/////////////// LUA API ///////////////////////////////////////////////////////
	public:
		// Tagged container for unit pointer
		static void pushTaggedUnit(lua_State *L, cUnit* pointer);
		static auto getTaggedUnit(lua_State *L, int indx) -> cUnit*;

		static void registerUnitApi(lua_State *L);

		static int l_getPos(lua_State *L);		// Get unit pos
		static int l_offset(lua_State *L);		// Offset unit pos
		static int l_resetOffset(lua_State *L);		// Reset unit offset

		static int l_getFirstItem(lua_State *L);	// Get first item in inventory(nil if none)
		static int l_getPhysical(lua_State *L);		// Get physical stats STR, DEF
		static int l_getHP(lua_State *L);		// Get HP of unit

		static int l_damage(lua_State *L);		// Deal damage to unit
		static int l_heal(lua_State* L);		// Heal unit
};
