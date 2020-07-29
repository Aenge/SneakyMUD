#pragma once
#include "Landscape/SectorManager.hpp"
namespace sneaky {
namespace World {
	class World {
	public:
		Landscape::SectorManager& getSectorManager();
	private:
		Landscape::SectorManager m_sectorManager;
	};
}}