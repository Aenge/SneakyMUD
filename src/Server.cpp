#include "../include/Server.hpp"
#include "../include/IO/Net/NetworkHandler.hpp"
#include "../include/IO/Net/Net235.hpp"
#include <iostream>
#include <string>
#include <thread>

using namespace sneaky;

Server::Server(const std::string& a_configPath) {
    if (!a_configPath.empty()) {
        if (m_configuration.load(a_configPath)) {
            std::cout << "[Server] Config successfully loaded" << std::endl;
        }
        else {
            std::cerr << "[Error] Error loading config" << std::endl;
            return;
        }
    }

    if (m_configuration.NETWORK_PROTOCOL == IO::Net::Protocol::p235) {
        m_networkHandler = std::make_shared<IO::Net::Net235>(m_configuration.NETWORK_PORT, m_configuration.SERVER_PLAYER_LIMIT);
    }
}

void Server::loop() {
    while (true) {
        Sleep(1000);
    }
}

void Server::start() {
    if (m_networkHandler == nullptr) {
        std::cerr << "[Error] No valid protocol specified" << std::endl;
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