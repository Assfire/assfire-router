#include <grpc++/server_builder.h>

#include "ArgsSettingsLoader.hpp"
#include "PropsSettingsLoader.hpp"
#include "RouterServiceImpl.hpp"
#include "ConfigurationServiceImpl.hpp"
#include "assfire/router/engine/BasicRoutingStrategyProvider.hpp"
#include "assfire/router/engine/BasicTransportProfileProvider.hpp"

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
void init_sockets()
{
}
void cleanup_sockets() {}
#endif

int main(int argc, char **argv)
{
    init_sockets();

    Settings settings;
    ArgsSettingsLoader().load_settings(settings);
    PropsSettingsLoader().load_settings(settings);

    std::cout << "Creating service" << std::endl;

    std::shared_ptr<RoutingStrategyProvider> routing_strategy_provider = std::make_shared<BasicRoutingStrategyProvider>();
    std::shared_ptr<TransportProfileProvider> transport_profile_provider = std::make_shared<BasicTransportProfileProvider>();

    RouterServiceImpl router_service(std::make_unique<RouterEngine>(routing_strategy_provider, transport_profile_provider));
    ConfigurationServiceImpl configuration_service(routing_strategy_provider, transport_profile_provider);

    std::cout << "Creating server" << std::endl;

    grpc::ServerBuilder server_builder;
    server_builder.AddListeningPort(settings.format_bind_address(), grpc::InsecureServerCredentials()); // [TODO] Perform TLS
    server_builder.RegisterService(&router_service);
    server_builder.RegisterService(&configuration_service);

    std::cout << "Building server service" << std::endl;

    std::unique_ptr<grpc::Server> server(server_builder.BuildAndStart());

    std::cout << "Starting listening" << std::endl;

    server->Wait();

    cleanup_sockets();
    return 0;
}