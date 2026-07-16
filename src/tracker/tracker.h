#pragma once

#include <string>
#include <cstdint>

struct Tracker{
    std::string protocol;
    std::string host;
    uint16_t port;
    std::string path;
};