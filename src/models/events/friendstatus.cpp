#include "friendstatus.h"

#include "src/models/enums/userstatus_p.h"

#include <QString>

#include <tox/tox_events.h>

namespace Events {
FriendStatus::FriendStatus(const Tox_Event_Friend_Status* event)
    : status(Enums::fromTox(tox_event_friend_status_get_status(event)))
    , friendNumber(tox_event_friend_status_get_friend_number(event))
{
}

FriendStatus::~FriendStatus() = default;

QString FriendStatus::toString() const
{
    return QStringLiteral("FriendStatus(status: %1, friendNumber: %2)")
        .arg(Enums::toString(status))
        .arg(friendNumber);
}
} // namespace Events
