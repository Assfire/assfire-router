#pragma once

#include <string>
#include <memory>
#include <grpcpp/channel.h>
#include <grpcpp/create_channel.h>

namespace assfire::router
{
    class RouterConnectionSettings
    {
    public:
        RouterConnectionSettings() : _server_address("localhost:50051"){};

        void set_server_address(const std::string &value)
        {
            this->_server_address = value;
        }

        const std::string &server_address() const
        {
            return _server_address;
        }

        std::shared_ptr<::grpc::ChannelCredentials> build_credentials() const {
            return ::grpc::InsecureChannelCredentials();
        }

    private:
        std::string _server_address;
    };
}