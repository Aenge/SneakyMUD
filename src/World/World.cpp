#include "../../include/World/World.hpp"

using namespace sneaky::World;

Landscape::SectorManager& World::getSectorManager() {
	return m_sectorManager;
}