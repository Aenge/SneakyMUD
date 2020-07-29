#pragma once
#include <array>
#include "Tile.hpp"
#include "../Constants.hpp"
namespace sneaky {
namespace World {
namespace Landscape {
	class Sector {
	public:
		std::array<Tile, SECTOR_SIZE*SECTOR_SIZE> m_tiles;
	};
}}}