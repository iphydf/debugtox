#pragma once

#include "src/models/bytes/bytearray.h"
#include "src/models/coreevent.h"

#include <cstdint>

class QString;
struct Tox_Event_Group_Peer_Name;

namespace Events {
class GroupPeerName final : public CoreEvent
{
public:
    explicit GroupPeerName(const Tox_Event_Group_Peer_Name* event);
    ~GroupPeerName() override;
    QString toString() const override;

    const uint32_t groupNumber;
    const uint32_t peerId;
    const ByteArray name;
};
} // namespace Events
