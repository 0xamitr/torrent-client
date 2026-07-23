#pragma once

#include <vector>
#include "tracker.h"
#include <mutex>

void udpTracker(const Torrent &torrent, const Tracker& tracker, std::unordered_set<Peer, PeerHash>& peers,  std::mutex &peersMutex);
