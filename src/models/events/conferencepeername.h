#pragma once

#include "src/models/bytes/bytearray.h"
#include "src/models/coreevent.h"

#include <cstdint>

class QString;
struct Tox_Event_Conference_Peer_Name;

namespace Events {
class ConferencePeerName final : public CoreEvent
{
public:
    explicit ConferencePeerName(const Tox_Event_Conference_Peer_Name* event);
    ~ConferencePeerName() override;
    QString toString() const override;

    const ByteArray name;
    const uint32_t conferenceNumber;
    const uint32_t peerNumber;
};
} // namespace Events
