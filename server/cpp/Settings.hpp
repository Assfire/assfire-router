#pragma once

#include <string>

namespace assfire::router
{
    enum class LogLevel
    {
        TRACE_LOG,
        DEBUG_LOG,
        INFO_LOG,
        WARN_LOG,
        ERROR_LOG,
        CRITICAL_LOG
    };

    class Settings
    {
    public:
        Settings() : _bind_address("0.0.0.0"),
                     _bind_port(50051),
                     _log_level(LogLevel::INFO_LOG)
        {
        }

        const std::string &bind_address() const
        {
            return _bind_address;
        }

        int bind_port() const
        {
            return _bind_port;
        }

        std::string format_bind_address() const
        {
            return _bind_address + ":" + std::to_string(_bind_port);
        }

        LogLevel log_level() const
        {
            return _log_level;
        }

        void set_bind_address(const std::string &bind_address)
        {
            _bind_address = bind_address;
        }

        void set_bind_port(int bind_port)
        {
            _bind_port = bind_port;
        }

        void set_log_level(LogLevel log_level)
        {
            _log_level = log_level;
        }

    private:
        std::string _bind_address;
        int _bind_port;
        LogLevel _log_level;
    };
}