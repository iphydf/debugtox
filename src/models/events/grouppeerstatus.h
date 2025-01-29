#pragma once

#include "src/models/enums/userstatus.h"
#include "src/models/coreevent.h"

#include <cstdint>

class QString;
struct Tox_Event_Group_Peer_Status;

namespace Events {
class GroupPeerStatus final : public CoreEvent
{
public:
    explicit GroupPeerStatus(const Tox_Event_Group_Peer_Status* event);
    ~GroupPeerStatus() override;
    QString toString() const override;

    const uint32_t groupNumber;
    const uint32_t peerId;
    const ::UserStatus::Type status;
};
} // namespace Events
