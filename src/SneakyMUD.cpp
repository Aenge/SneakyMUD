#include <iostream>
#include "../include/Server.hpp"
#include <filesystem>
#include <string>
std::string configPath{ "" };
bool fatal{ false };
void parse(const int& argc, char* argv[]);

int main(int argc, char* argv[]) {
    parse(argc, argv);
    if (fatal) {
        return 1;
    }

    sneaky::Server server(configPath);
    server.start();    
    return 0;
}

void parse(const int& argc, char* argv[]) {
    if (argc == 1) {
        std::cerr << "[Warning] No config file specified" << std::endl;
    }
    else if (argc == 2) {
        if (!std::filesystem::exists(argv[1])) {
            std::cerr << "[Error] Specified config file cannot be found" << std::endl;
            fatal = true;
            return;
        }
        configPath = argv[1];
    }
    else {
        std::cerr << "[Error] Expected one argument. Found " << argc-1 << std::endl;
        fatal = true;
    }
}
