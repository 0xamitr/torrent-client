#include <vector>
#include "tracker.h"
#include "../torrent/torrent.h"
#include "udptracker.h"
#include "httptracker.h"
#include <unordered_set>
#include <vector>
#include <thread>
#include <mutex>

std::unordered_set<Peer, PeerHash> getTracker(const Torrent &torrent)
{
    std::vector<std::thread> threads;
    std::unordered_set<Peer, PeerHash> peers;
    std::mutex peersMutex;

    for (const auto &tracker : torrent.trackers)
    {
        threads.emplace_back([&, tracker]()
                             {
            if (tracker.protocol == "http" || tracker.protocol == "https")
                httpTracker(torrent, tracker, peers, peersMutex);
            else if (tracker.protocol == "udp")
                udpTracker(torrent, tracker, peers, peersMutex); });
    }
    for (auto &t : threads)
    {
        t.join();
    }
    return peers;
}