#pragma once

#include <string>
#include <cstdint>
#include <array>
#include <vector>
#include <unordered_set>
struct Torrent;

struct Tracker
{
    std::string protocol;
    std::string host;
    uint16_t port;
    std::string path;
};

struct Peer
{
    std::array<uint8_t, 16> ip{};
    uint16_t port{};
    bool isIPv6{};

    bool operator==(const Peer &other) const
    {
        return ip == other.ip &&
               port == other.port &&
               isIPv6 == other.isIPv6;
    }
};

struct PeerHash
{
    size_t operator()(const Peer &p) const
    {
        size_t h = 0;

        for (uint8_t b : p.ip)
        {
            h ^= std::hash<uint8_t>{}(b) + 0x9e3779b9 + (h << 6) + (h >> 2);
        }

        h ^= std::hash<uint16_t>{}(p.port) + 0x9e3779b9 + (h << 6) + (h >> 2);

        h ^= std::hash<bool>{}(p.isIPv6) + 0x9e3779b9 + (h << 6) + (h >> 2);

        return h;
    }
};

std::unordered_set<Peer, PeerHash> getTracker(const Torrent &torrent);