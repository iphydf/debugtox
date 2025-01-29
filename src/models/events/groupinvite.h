#pragma once

#include "src/models/bytes/bytearray.h"
#include "src/models/coreevent.h"

#include <cstdint>

class QString;
struct Tox_Event_Group_Invite;

namespace Events {
class GroupInvite final : public CoreEvent
{
public:
    explicit GroupInvite(const Tox_Event_Group_Invite* event);
    ~GroupInvite() override;
    QString toString() const override;

    const uint32_t friendNumber;
    const ByteArray inviteData;
    const ByteArray groupName;
};
} // namespace Events
