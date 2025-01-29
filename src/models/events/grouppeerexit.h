#pragma once

#include "src/models/bytes/bytearray.h"
#include "src/models/enums/groupexittype.h"
#include "src/models/coreevent.h"

#include <cstdint>

class QString;
struct Tox_Event_Group_Peer_Exit;

namespace Events {
class GroupPeerExit final : public CoreEvent
{
public:
    explicit GroupPeerExit(const Tox_Event_Group_Peer_Exit* event);
    ~GroupPeerExit() override;
    QString toString() const override;

    const uint32_t groupNumber;
    const uint32_t peerId;
    const ::GroupExitType::Type exitType;
    const ByteArray name;
    const ByteArray partMessage;
};
} // namespace Events
