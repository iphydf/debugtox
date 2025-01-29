#pragma once

#include "src/models/bytes/bytearray.h"
#include "src/models/coreevent.h"

#include <cstdint>

class QString;
struct Tox_Event_Group_Custom_Packet;

namespace Events {
class GroupCustomPacket final : public CoreEvent
{
public:
    explicit GroupCustomPacket(const Tox_Event_Group_Custom_Packet* event);
    ~GroupCustomPacket() override;
    QString toString() const override;

    const uint32_t groupNumber;
    const uint32_t peerId;
    const ByteArray data;
};
} // namespace Events
