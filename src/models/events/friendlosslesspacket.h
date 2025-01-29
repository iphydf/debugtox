#pragma once

#include "src/models/bytes/bytearray.h"
#include "src/models/coreevent.h"

#include <cstdint>

class QString;
struct Tox_Event_Friend_Lossless_Packet;

namespace Events {
class FriendLosslessPacket final : public CoreEvent
{
public:
    explicit FriendLosslessPacket(const Tox_Event_Friend_Lossless_Packet* event);
    ~FriendLosslessPacket() override;
    QString toString() const override;

    const ByteArray data;
    const uint32_t friendNumber;
};
} // namespace Events
