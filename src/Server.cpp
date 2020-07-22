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
    //Check for supplied config file
    if (a_configPath.empty()) {
        std::cout << "[Warning] No config file specified" << std::endl;
    }
    else if (!std::filesystem::exists(a_configPath)) {
        std::cout << "[Error] Specified config file cannot be found" << std::endl;
        return false;
    }
    else {
        if (!m_configuration.load(a_configPath))
            return false;
    }

    if (!processConfig())
        return false;

    m_initialized = true;
    return true;
}

bool Server::processConfig() {
    std::filesystem::path configDirectory = m_configuration.FILE_PATH.parent_path();
    //Network
    if (m_configuration.NET_PROTOCOL == IO::Net::Protocol::p235) {
        m_networkHandler = std::make_shared<IO::Net::Net235>(m_configuration.NET_PORT, m_configuration.SERVER_PLAYER_LIMIT);
    }
    else {
        std::cerr << "[Error] No valid network protocol specified" << std::endl;
        return false;
    }

    //Definitions
    if (m_configuration.DEF_LANDSCAPE.empty()) {
        std::cout << "[Warning] No landscape definition specified" << std::endl;
    }
    else if (!std::filesystem::exists(configDirectory / m_configuration.DEF_LANDSCAPE)) {
        std::cout << "[Error] Specified landscape definition not found" << std::endl;
        return false;
    }
    else {
    }

    if (m_configuration.DEF_SCENERY.empty()) {
        std::cout << "[Warning] No scenery definition specified" << std::endl;
    }
    else if (!std::filesystem::exists(configDirectory / m_configuration.DEF_SCENERY)) {
        std::cout << "[Error] Specified scenery definition not found" << std::endl;
        return false;
    }
    else {
    }

    if (m_configuration.DEF_NPC.empty()) {
        std::cout << "[Warning] No npc definition specified" << std::endl;
    }
    else if (!std::filesystem::exists(configDirectory / m_configuration.DEF_NPC)) {
        std::cout << "[Error] Specified npc definition not found" << std::endl;
        return false;
    }
    else {
    }
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
            std::cout << "[" << m_configuration.SERVER_NAME << "] Starting on port " << m_configuration.NET_PORT << std::endl;
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