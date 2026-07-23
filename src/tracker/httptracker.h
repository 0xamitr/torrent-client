#pragma once

#include "../torrent/torrent.h"
#include "tracker.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string>
#include <cstring>
#include <arpa/inet.h>
#include <iostream>
#include <vector>
#include <mutex>

void httpTracker(const Torrent &torrent, const Tracker &tracker, std::unordered_set<Peer, PeerHash> &peers, std::mutex &peersMutex);
std::string urlEncode(const uint8_t *data, size_t len);
void getPeersfromResponse(std::string response, std::unordered_set<Peer, PeerHash> &peers, std::mutex &peersMutex);
bool isIPv6(const std::string &ip);