#pragma once
#include "Net/NetworkHandler.hpp"
#include <string>

namespace sneaky {
namespace IO {
	class Configuration {
	public:
		Configuration();
		bool load(const std::string& a_path);

		//General
		std::string SERVER_NAME{ "SneakyMUD" };
		int SERVER_PLAYER_LIMIT{ 100 };

		//Network
		Net::Protocol NETWORK_PROTOCOL{ Net::Protocol::p235 };
		int NETWORK_PORT{ 43594 };

		//Definitions
		std::string DEF_NPC{ "" };
		std::string DEF_SCENERY{ "" };
	};
} }