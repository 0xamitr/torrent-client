#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include <array>
#include "../tracker/tracker.h"

struct Torrent
{
    std::vector<Tracker> trackers;

    std::string name;
    int64_t length;
    int64_t piecelength;

    std::vector<std::array<uint8_t, 20>> pieceHashes;
    std::array<uint8_t, 20> infoHash;
};

Torrent LoadTorrent(const std::string &filename);