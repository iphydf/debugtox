#pragma once

#include "src/models/enums/connection.h"
#include "src/models/coreevent.h"

#include <cstdint>

class QString;
struct Tox_Event_Friend_Connection_Status;

namespace Events {
class FriendConnectionStatus final : public CoreEvent
{
public:
    explicit FriendConnectionStatus(const Tox_Event_Friend_Connection_Status* event);
    ~FriendConnectionStatus() override;
    QString toString() const override;

    const ::Connection::Type connectionStatus;
    const uint32_t friendNumber;
};
} // namespace Events
