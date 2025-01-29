#pragma once

#include "src/models/enums/userstatus.h"
#include "src/models/coreevent.h"

#include <cstdint>

class QString;
struct Tox_Event_Friend_Status;

namespace Events {
class FriendStatus final : public CoreEvent
{
public:
    explicit FriendStatus(const Tox_Event_Friend_Status* event);
    ~FriendStatus() override;
    QString toString() const override;

    const ::UserStatus::Type status;
    const uint32_t friendNumber;
};
} // namespace Events
