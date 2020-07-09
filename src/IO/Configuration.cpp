#include "../../include/IO/Configuration.hpp"
#include "../../include/external/yaml/include/yaml-cpp/yaml.h"
#include <string>
#include <iostream>

using namespace sneaky::IO;

Configuration::Configuration() {
	
}

bool Configuration::load(const std::string& a_path) {
	try {
		YAML::Node config = YAML::LoadFile(a_path);
		//General
		SERVER_NAME = config["name"].as<std::string>();
		SERVER_PLAYER_LIMIT = config["player_limit"].as<int>();

		//Network
		NETWORK_PROTOCOL = static_cast<Net::Protocol>(config["protocol"].as<int>());
		NETWORK_PORT = config["port"].as<int>();
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return false;
	}
	
	return true;
}

