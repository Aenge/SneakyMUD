#include "../include/Server.hpp"
#include "../include/IO/Net/NetworkHandler.hpp"
#include "../include/IO/Net/Net235.hpp"
#include <iostream>
#include <string>
#include <thread>
#include <filesystem>

using namespace sneaky;

void checkpath(const std::string& a_name, const std::string& a_path, bool& a_result);

Server::Server() {
    
}

bool Server::init(const std::string& a_configPath) {
    bool fatal = false;
    checkpath("config file", a_configPath, fatal);

    if (!fatal && !a_configPath.empty()) {
        m_configuration.load(a_configPath);
        std::filesystem::current_path(std::filesystem::path(a_configPath).parent_path());
    }

    //Network
    if (m_configuration.NETWORK_PROTOCOL == IO::Net::Protocol::p235) {
        m_networkHandler = std::make_shared<IO::Net::Net235>(m_configuration.NETWORK_PORT, m_configuration.SERVER_PLAYER_LIMIT);
    }
    else {
        std::cerr << "[Error] No valid network protocol specified" << std::endl;
        fatal = true;
    }

    //Definitions
    checkpath("NPC definitions", m_configuration.DEF_NPC, fatal);
    checkpath("scenery definitions", m_configuration.DEF_SCENERY, fatal);

    if (!fatal)
        m_initialized = true;

    return !fatal;
}
void Server::loop() {
    while (true) {
        Sleep(1000);
    }
}

void Server::start() {
    if (!m_initialized) {
        std::cerr << "[Error] Must call server.init() before server.start()" << std::endl;
        return;
    }

    std::thread t(
        [this]() {
            std::cout << "[" << m_configuration.SERVER_NAME << "] Starting on port " << m_configuration.NETWORK_PORT << std::endl;
            try {
                m_networkHandler->listen();
                m_networkHandler->getIOService()->run();
            }
            catch (std::exception& e) {
                std::cerr << e.what() << std::endl;
            }
        });

    loop();
}

const IO::Configuration& Server::getConfig() {
    return m_configuration;
} 

void checkpath(const std::string& a_name, const std::string& a_path, bool& a_result) {
    if (a_path.empty()) {
        std::cerr << "[Warning] No " << a_name << " specified" << std::endl;
    }
    else {
        if (!std::filesystem::exists(a_path)) {
            std::cerr << "[Error] Cannot find " << a_name << std::endl;
            a_result = true;
        }
    }
}