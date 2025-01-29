#pragma once

#include "src/models/coreevent.h"

#include <cstdint>

class QString;
struct Tox_Event_Group_Peer_Join;

namespace Events {
class GroupPeerJoin final : public CoreEvent
{
public:
    explicit GroupPeerJoin(const Tox_Event_Group_Peer_Join* event);
    ~GroupPeerJoin() override;
    QString toString() const override;

    const uint32_t groupNumber;
    const uint32_t peerId;
};
} // namespace Events
