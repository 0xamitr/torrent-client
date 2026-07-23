#pragma once

#include "../tracker/tracker.h"
#include "peer.h"
#include <vector>
int connectPeer(const Peer &peer, std::vector<PeerConnection> &connectedPeer);
