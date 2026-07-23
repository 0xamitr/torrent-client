#include <../../tracker/tracker.h>
#include <string>

Tracker trackerParser(const std::string link)
{
    Tracker tracker;
    std::string protocol = "";
    std::string host = "";
    uint16_t port = 0;
    std::string path = "";
    size_t len = link.size();
    size_t i = 0;
    while (i < len)
    {
        if (link[i] == ':')
            break;
        protocol += link[i++];
    }
    i += 3;
    while (i < len)
    {
        if (link[i] == ':' || link[i] == '/')
            break;
        host += link[i++];
    }
    if (link[i] == ':')
        i++;
    while (i < len)
    {
        if (link[i] == '/')
            break;
        port = port * 10 + link[i++] - '0';
    }
    while (i < len)
    {
        path += link[i++];
    }

    tracker.protocol = protocol;
    tracker.host = host;
    tracker.path = path;
    if (port == 0)
    {
        if (protocol == "http")
            tracker.port = 80;
        else if (protocol == "https")
            tracker.port = 443;
    }
    else
    {
        tracker.port = port;
    }

    return tracker;
}