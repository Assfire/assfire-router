#pragma once

#include <grpc++/server_builder.h>

#include "ArgsSettingsLoader.hpp"
#include "PropsSettingsLoader.hpp"
#include "RouterServiceImpl.hpp"

#include <iostream>

using namespace assfire::router;

#ifdef WIN32
#include <WinSock2.h>
#include <stdexcept>

void init_sockets()
{
    WORD version = MAKEWORD(2, 2);
    WSADATA data;
    if (WSAStartup(version, &data) != 0)
    {
        throw std::runtime_error("Winsock error: " + std::to_string(WSAGetLastError()));
    }
}
void cleanup_sockets()
{
    WSACleanup();
}
#else 
void init_sockets() {}
void cleanup_sockets() {}
#endif

int main(int argc, char **argv)
{
    init_sockets();

    Settings settings;
    ArgsSettingsLoader().load_settings(settings);
    PropsSettingsLoader().load_settings(settings);

    std::cout << "Creating service" << std::endl;

    RouterServiceImpl service(std::make_unique<RouterEngine>(
        std::unique_ptr<RoutingStrategyProvider>(nullptr), // [TODO]
        std::unique_ptr<TransportProfileProvider>(nullptr) // [TODO]
        ));

    std::cout << "Creating server" << std::endl;

    grpc::ServerBuilder server_builder;
    server_builder.AddListeningPort(settings.format_bind_address(), grpc::InsecureServerCredentials()); // [TODO] Perform TLS
    server_builder.RegisterService(&service);

    std::cout << "Building server service" << std::endl;

    std::unique_ptr<grpc::Server> server(server_builder.BuildAndStart());

    std::cout << "Starting listening" << std::endl;

    server->Wait();

    cleanup_sockets();
    return 0;
}