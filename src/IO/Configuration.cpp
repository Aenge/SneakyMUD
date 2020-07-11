#include "../../include/IO/Configuration.hpp"
#include "../../include/external/yaml/include/yaml-cpp/yaml.h"
#include <string>
#include <iostream>

using namespace sneaky::IO;
using namespace YAML;

Configuration::Configuration() {
	
}

bool Configuration::load(const std::string& a_path) {
	try {
		YAML::Node config = YAML::LoadFile(a_path);
		YAML::Node node;
		//General
		if (node = config["name"]) SERVER_NAME = node.as<std::string>();
		if (node = config["player_limit"]) SERVER_PLAYER_LIMIT = node.as<int>();

		//Network
		if (node = config["net_protocol"]) NETWORK_PROTOCOL = static_cast<Net::Protocol>(node.as<int>());
		if (node = config["net_port"]) NETWORK_PORT = node.as<int>();

		//Definitions
		if (node = config["def_npc"]) DEF_NPC = node.as<std::string>();
		if (node = config["def_scenery"]) DEF_SCENERY = node.as<std::string>();
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return false;
	}
	
	return true;
}

