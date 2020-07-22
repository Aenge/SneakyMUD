#pragma once
#include "../include/IO/Net/NetworkHandler.hpp"
#include "../include/IO/Net/Net235.hpp"
#include "../include/IO/Configuration.hpp"
#include "../include/World/World.hpp"
#include <string>

namespace sneaky{
    class Server {
    public:
        Server();
        bool init(const std::string& a_configPath);
        bool processConfig();
        void start();
        const IO::Configuration& getConfig();
    private:
        World::World m_world;
        IO::Configuration m_configuration;
        std::shared_ptr<IO::Net::NetworkHandler> m_networkHandler{ nullptr };
        bool m_initialized{ false };

        void loop();
    };
}