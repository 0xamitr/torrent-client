#pragma once

#include "../tracker/tracker.h"
#include "peer.h"

bool handShake(PeerConnection &peerconnection, std::array<uint8_t, 20> &infoHash);
