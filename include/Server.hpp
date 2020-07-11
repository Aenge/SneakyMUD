#pragma once
#include "../include/IO/Net/NetworkHandler.hpp"
#include "../include/IO/Net/Net235.hpp"
#include "../include/IO/Configuration.hpp"
#include <string>

namespace sneaky{
    class Server {
    public:
        Server();
        bool init(const std::string& a_configPath);
        void start();
        const IO::Configuration& getConfig();
    private:
        IO::Configuration m_configuration;
        std::shared_ptr<IO::Net::NetworkHandler> m_networkHandler{ nullptr };
        bool m_initialized{ false };
        void loop();
    };
}