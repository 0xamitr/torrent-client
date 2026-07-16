#include "tracker.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string>
#include <cstring>

void udpTracker(Tracker tracker)
{
    struct addrinfo hints;
    struct addrinfo *servinfo;
    memset(&hints, 0, sizeof hints);
    
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    std::string port = std::to_string(tracker.port);
    int result = getaddrinfo(
        tracker.host.c_str(),
        port.c_str(),
        &hints,
        &servinfo
    );
}