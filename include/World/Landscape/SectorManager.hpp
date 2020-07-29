#pragma once
#include "Sector.hpp"
#include "../../IO/ByteStream.hpp"
#include "../Constants.hpp"
#include <array>
#include <memory>

namespace sneaky {
namespace World {
namespace Landscape {
	class SectorManager {
	public:
		SectorManager();
		bool loadSector(const uint8_t& a_floor, const uint8_t a_x, const uint8_t a_y, IO::ByteStream& a_bytestream);
	private:
		std::array<std::unique_ptr<Sector>, WORLD_FLOORS*FLOOR_WIDTH*FLOOR_HEIGHT> m_sectors;
	};
}
}
}