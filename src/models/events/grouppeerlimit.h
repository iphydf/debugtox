#pragma once

#include "src/models/coreevent.h"

#include <cstdint>

class QString;
struct Tox_Event_Group_Peer_Limit;

namespace Events {
class GroupPeerLimit final : public CoreEvent
{
public:
    explicit GroupPeerLimit(const Tox_Event_Group_Peer_Limit* event);
    ~GroupPeerLimit() override;
    QString toString() const override;

    const uint32_t groupNumber;
    const uint32_t peerLimit;
};
} // namespace Events
