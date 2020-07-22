#pragma once
#include "Net/NetworkHandler.hpp"
#include <filesystem>
#include <string>

namespace sneaky {
namespace IO {
	class Configuration {
	public:
		Configuration();
		bool load(const std::string& a_path);
		std::filesystem::path FILE_PATH{ "" };

		//General
		std::string SERVER_NAME{ "SneakyMUD" };
		int SERVER_PLAYER_LIMIT{ 100 };

		//Network
		Net::Protocol NET_PROTOCOL{ Net::Protocol::p235 };
		int NET_PORT{ 43594 };

		//Definitions
		std::string DEF_NPC{ "" };
		std::string DEF_SCENERY{ "" };
		std::string DEF_LANDSCAPE{ "" };

		//Content
		bool CON_MEMBERS{ false };
	};
} }