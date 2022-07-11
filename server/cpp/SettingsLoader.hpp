#pragma once

#include "Settings.hpp"

namespace assfire::router
{
    class SettingsLoader
    {
    public:
        virtual void load_settings(Settings &out_settings) = 0;
    };
}