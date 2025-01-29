#pragma once

#include "src/models/bytes/bytearray.h"
#include "src/models/coreevent.h"

#include <cstdint>

class QString;
struct Tox_Event_Friend_Lossy_Packet;

namespace Events {
class FriendLossyPacket final : public CoreEvent
{
public:
    explicit FriendLossyPacket(const Tox_Event_Friend_Lossy_Packet* event);
    ~FriendLossyPacket() override;
    QString toString() const override;

    const ByteArray data;
    const uint32_t friendNumber;
};
} // namespace Events
