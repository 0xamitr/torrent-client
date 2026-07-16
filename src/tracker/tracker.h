#pragma once

#include <string>
#include <cstdint>
#include <array>

struct Tracker
{
    std::string protocol;
    std::string host;
    uint16_t port;
    std::string path;
};

struct Peer
{
    std::array<uint8_t, 4> ip;
    uint16_t port;
};