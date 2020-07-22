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
		FILE_PATH = std::filesystem::path(a_path);

		YAML::Node config = YAML::LoadFile(a_path);
		YAML::Node node;
		//General
		if (node = config["name"]) SERVER_NAME = node.as<std::string>();
		if (node = config["player_limit"]) SERVER_PLAYER_LIMIT = node.as<int>();

		//Network
		if (node = config["net_protocol"]) NET_PROTOCOL = static_cast<Net::Protocol>(node.as<int>());
		if (node = config["net_port"]) NET_PORT = node.as<int>();

		//Definitions
		if (node = config["def_npc"]) DEF_NPC = node.as<std::string>();
		if (node = config["def_scenery"]) DEF_SCENERY = node.as<std::string>();
		if (node = config["def_landscape"]) DEF_LANDSCAPE = node.as<std::string>();

		//Content
		if (node = config["con_members"]) CON_MEMBERS = node.as<bool>();

	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return false;
	}
	
	return true;
}

