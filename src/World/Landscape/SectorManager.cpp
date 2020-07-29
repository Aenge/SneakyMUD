#include "../../../include/World/Landscape/SectorManager.hpp"
#include <iostream>
using namespace sneaky::World::Landscape;

SectorManager::SectorManager() {
	std::fill(m_sectors.begin(), m_sectors.end(), nullptr);
}

bool SectorManager::loadSector(const uint8_t& a_floor, const uint8_t a_x, const uint8_t a_y, IO::ByteStream& a_bytestream)
{
	//TODO: Clean this up
	int element = static_cast<int>(a_floor) * FLOOR_HEIGHT * FLOOR_WIDTH;
	element += static_cast<int>(a_y - (FLOOR_Y_OFFSET / SECTOR_SIZE)) * FLOOR_HEIGHT;
	element += static_cast<int>(a_x - (FLOOR_X_OFFSET / SECTOR_SIZE));
	//std::cout << element << " / " << m_sectors.size() << std::endl;
	if (m_sectors[element] != nullptr) {
		std::cerr << "[Error] Previously defined sector attempting to load again" << std::endl;
		return false;
	}

	try{
		m_sectors[element] = std::make_unique<Sector>();
		//Diag wall horiz
		for (int i = 0; i < m_sectors[element].get()->m_tiles.size(); ++i) {
				m_sectors[element].get()->m_tiles[i].nowal = a_bytestream.readUnsignedByte();
		}
		//Diag wall vert
		for (int i = 0; i < m_sectors[element].get()->m_tiles.size(); ++i) {
			m_sectors[element].get()->m_tiles[i].nowal2 = a_bytestream.readUnsignedByte();
		}
		//Horiz wall?
		for (int i = 0; i < m_sectors[element].get()->m_tiles.size(); ++i) {
			m_sectors[element].get()->m_tiles[i].nowal3 = a_bytestream.readUnsignedByte();
		}
		//Vert wall?
		for (int i = 0; i < m_sectors[element].get()->m_tiles.size(); ++i) {
			m_sectors[element].get()->m_tiles[i].nowal4 = a_bytestream.readUnsignedByte();
		}
		//Roof?
		for (int i = 0; i < m_sectors[element].get()->m_tiles.size(); ++i) {
			uint8_t roof = a_bytestream.readUnsignedByte();
			m_sectors[element].get()->m_tiles[i].nowal5 = roof;
			if (roof >= 128)
				i += roof - 129;
		}
		//Tile decoration?
		for (int i = 0; i < m_sectors[element].get()->m_tiles.size(); ++i) {
			uint8_t decoration = a_bytestream.readUnsignedByte();
			m_sectors[element].get()->m_tiles[i].nowal6 = decoration;
			if (decoration >= 128)
				i += decoration - 129;
		}
		//Tile direction?
		for (int i = 0; i < m_sectors[element].get()->m_tiles.size(); ++i) {
			uint8_t direction = a_bytestream.readUnsignedByte();
			m_sectors[element].get()->m_tiles[i].nowal7 = direction;
			if (direction >= 128)
				i += direction - 129;
		}
	}
	catch (std::exception &a) {
		std::cerr << a.what() << std::endl;
		std::cerr << "huh";
		return false;
	}
	
	//printf("Loading f: %d x: %d y: %d %d %d %d %d\n", a_floor, a_x, a_y, m_sectors[element].get()->m_tiles[35][35].nowal, m_sectors[element].get()->m_tiles[35][35].nowal2, m_sectors[element].get()->m_tiles[35][35].nowal3, m_sectors[element].get()->m_tiles[35][35].nowal4);
	return true;
}
