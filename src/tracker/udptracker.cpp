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

std::vector<Peer> udpTracker(const Torrent &torrent)
{
    uint16_t clientPort = 6881;
    Tracker tracker = torrent.trackers[0];
    // we provide hints when calling getaddrinfo() which gets the ip adresses
    // from the dns server among other things, these hints include the type of socket
    // we want to use, could be stream or dgram(connection less)
    // we also set a value to ai_family which tells the getaddrinfo() which IP address
    // we want from the dns (ipv4 or ipv6)
    // we set it to 0 or AF_UNSPEC which basically tells it that we don't care and it
    // could use either.
    struct addrinfo hints;
    struct addrinfo *servinfo;

    // we basically remove any garbage values that there might be in hints
    memset(&hints, 0, sizeof hints);

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;

    std::string port = std::to_string(tracker.port);

    // this populates the servinfo
    int status = getaddrinfo(
        tracker.host.c_str(),
        port.c_str(),
        &hints,
        &servinfo);

    // creates a socket for communication
    // the third argument was ai_protocol (tcp, udp) but we dont need it in this case,
    // since our ai_socktype is sock_dgram which the kernel automatically configures as
    // UDP
    int sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, 0);

    connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen);

    uint64_t protocol_id = htobe64(0x41727101980);
    uint32_t action = htonl(0);
    uint32_t transaction_id = htonl(1);

    uint8_t packet[16];

    memcpy(packet, &protocol_id, 8);
    memcpy(packet + 8, &action, 4);
    memcpy(packet + 12, &transaction_id, 4);

    std::cout << "Sending package" << std::endl;
    size_t bytesSent = sendto(sockfd, packet, 16, 0, servinfo->ai_addr, servinfo->ai_addrlen);

    if (bytesSent == -1)
        perror("sendto");

    std::cout << "Bytes sent:" << bytesSent << std::endl;

    struct sockaddr_storage from;
    socklen_t fromlen = sizeof from;
    uint8_t buffer[16];
    uint32_t transaction_id_received;

    ssize_t bytesRead = recvfrom(sockfd, buffer, 16, 0, (struct sockaddr *)&from, &fromlen);

    std::cout << "bytes read: " << bytesRead << std::endl;

    uint64_t connection_id;
    memcpy(&action, buffer, 4);
    action = ntohl(action);
    memcpy(&transaction_id_received, buffer + 4, 4);
    transaction_id = ntohl(transaction_id);
    transaction_id_received = ntohl(transaction_id_received);
    memcpy(&connection_id, buffer + 8, 8);

    if (transaction_id != transaction_id_received)
    {
        perror("transaction IDs are not equal");
    }

    std::cout << "action: " << action << std::endl;
    std::cout << "transaction_id: " << transaction_id << std::endl;
    std::cout << "connection_id: " << connection_id << std::endl;

    uint8_t package[98];
    memset(&package, 0, 98);

    char peer_id[] = "-AM0001-123456789012";

    action = htonl(1);
    uint64_t downloaded = htobe64(0);
    uint64_t left = htobe64(torrent.length);
    uint64_t uploaded = htobe64(0);

    uint32_t event = htonl(0);           
    uint32_t ip = htonl(0);             
    uint32_t key = htonl(0x12345678);     
    uint32_t numWant = htonl(0xFFFFFFFF); 

    clientPort = htons(clientPort);

    memcpy(package, &connection_id, 8);
    memcpy(package + 8, &action, 4);
    memcpy(package + 12, &transaction_id, 4);
    memcpy(package + 16, torrent.infoHash.data(), 20);
    memcpy(package + 36, peer_id, 20);
    memcpy(package + 56, &downloaded, 8);
    memcpy(package + 64, &left, 8);
    memcpy(package + 72, &uploaded, 8);

    memcpy(package + 80, &event, 4);
    memcpy(package + 84, &ip, 4);
    memcpy(package + 88, &key, 4);
    memcpy(package + 92, &numWant, 4);
    memcpy(package + 96, &clientPort, 2);

    std::cout << "Sending peer request......" << std::endl;
    ssize_t bytesSentPeer = sendto(sockfd, package, 98, 0, servinfo->ai_addr, servinfo->ai_addrlen);
    std::cout << "bytes sent: " << bytesSentPeer << std::endl;

    uint8_t peerbuffer[1500];
    ssize_t bytesReadPeer = recvfrom(sockfd, peerbuffer, 1500, 0, (struct sockaddr *)&from, &fromlen);

    std::cout << "bytes read: " << bytesReadPeer << std::endl;

    uint32_t interval;
    uint32_t leeches;
    uint32_t seeders;
    memcpy(&action, peerbuffer, 4);
    memcpy(&transaction_id, peerbuffer + 4, 4);
    memcpy(&interval, peerbuffer + 8, 4);
    memcpy(&leeches, peerbuffer + 12, 4);
    memcpy(&seeders, peerbuffer + 16, 4);

    size_t n = 0;
    std::vector<Peer> p;
    while(20 + 6*n <= bytesReadPeer){
        Peer peer;
        memcpy(peer.ip.data(), peerbuffer + 20+6*n, 4);
        memcpy(&peer.port, peerbuffer + 24+6*n, 2);

        p.push_back(peer);
        n++;
    }


    interval = ntohl(interval);
    leeches = ntohl(leeches);
    action = ntohl(action);
    seeders = ntohl(seeders);

    std::cout << "interval: " << interval << std::endl;
    std::cout << "action: " << action << std::endl;
    std::cout << "leeches: " << leeches << std::endl;
    std::cout << "seeders: " << seeders << std::endl;
    return p;
}
