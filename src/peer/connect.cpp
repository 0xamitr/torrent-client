#include "../tracker/tracker.h"
#include <netinet/in.h>
#include <cstring>
#include <iostream>
#include <cerrno>
#include <unistd.h>
#include <fcntl.h>
#include "peer.h"

int connectPeer(const Peer &peer, std::vector<PeerConnection> &connectedPeer)
{
    int sockfd;
    std::cout << "port: " << peer.port << '\n';
    sockaddr_storage storage{};
    socklen_t len;

    if (peer.isIPv6)
    {
        auto *addr = reinterpret_cast<sockaddr_in6 *>(&storage);
        addr->sin6_family = AF_INET6;
        addr->sin6_port = htons(peer.port);
        memcpy(&addr->sin6_addr, peer.ip.data(), 16);

        sockfd = socket(AF_INET6, SOCK_STREAM, 0);
        len = sizeof(sockaddr_in6);
    }
    else
    {
        auto *addr = reinterpret_cast<sockaddr_in *>(&storage);
        addr->sin_family = AF_INET;
        addr->sin_port = htons(peer.port);
        memcpy(&addr->sin_addr, peer.ip.data(), 4);

        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        len = sizeof(sockaddr_in);
    }

    if (sockfd == -1)
    {
        perror("socket");
        return -1;
    }

    fcntl(sockfd, F_SETFL, O_NONBLOCK);

    int ret = connect(sockfd, (sockaddr *)&storage, len);

    if (ret == 0)
    {
        std::cout << "Connected immediately\n";
        PeerConnection peerconnection;
        peerconnection.peer = peer;
        peerconnection.socket = sockfd;
        peerconnection.interested = false;
        peerconnection.choked = true;
        connectedPeer.push_back(peerconnection);
    }
    else if (errno == EINPROGRESS)
    {
        fd_set writefds;
        FD_ZERO(&writefds);
        FD_SET(sockfd, &writefds);

        timeval tv{};
        tv.tv_sec = 2;
        tv.tv_usec = 0;

        ret = select(sockfd + 1, nullptr, &writefds, nullptr, &tv);

        if (ret == 0)
        {
            std::cerr << "Connection timed out\n";
            close(sockfd);
            return -1;
        }

        if (ret < 0)
        {
            perror("select");
            close(sockfd);
            return -1;
        }

        int err;
        socklen_t errlen = sizeof(err);

        if (getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &err, &errlen) < 0)
        {
            perror("getsockopt");
            close(sockfd);
            return -1;
        }

        if (err != 0)
        {
            errno = err;
            perror("connect");
            close(sockfd);
            return -1;
        }

        PeerConnection peerconnection;
        peerconnection.peer = peer;
        peerconnection.socket = sockfd;
        peerconnection.interested = false;
        peerconnection.choked = true;
        connectedPeer.push_back(peerconnection);
        std::cout << "Connected!\n";
    }
    else
    {
        perror("connect");
        close(sockfd);
        return -1;
    }
    int flags = fcntl(sockfd, F_GETFL, 0);
    fcntl(sockfd, F_SETFL, flags & ~O_NONBLOCK);
    return 0;
}