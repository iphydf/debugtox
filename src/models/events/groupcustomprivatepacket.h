#pragma once

#include "src/models/bytes/bytearray.h"
#include "src/models/coreevent.h"

#include <cstdint>

class QString;
struct Tox_Event_Group_Custom_Private_Packet;

namespace Events {
class GroupCustomPrivatePacket final : public CoreEvent
{
public:
    explicit GroupCustomPrivatePacket(const Tox_Event_Group_Custom_Private_Packet* event);
    ~GroupCustomPrivatePacket() override;
    QString toString() const override;

    const uint32_t groupNumber;
    const uint32_t peerId;
    const ByteArray data;
};
} // namespace Events
