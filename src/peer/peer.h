#pragma once
#include "../tracker/tracker.h"
#include <vector>

struct PeerConnection
{
    Peer peer;

    int socket;

    bool handshakeDone;

    bool choked;

    bool interested;

    std::vector<bool> bitfield;
};