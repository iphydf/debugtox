#include "friendconnectionstatus.h"

#include "src/models/enums/connection_p.h"

#include <QString>

#include <tox/tox_events.h>

namespace Events {
FriendConnectionStatus::FriendConnectionStatus(const Tox_Event_Friend_Connection_Status* event)
    : connectionStatus(Enums::fromTox(tox_event_friend_connection_status_get_connection_status(event)))
    , friendNumber(tox_event_friend_connection_status_get_friend_number(event))
{
}

FriendConnectionStatus::~FriendConnectionStatus() = default;

QString FriendConnectionStatus::toString() const
{
    return QStringLiteral("FriendConnectionStatus(connectionStatus: %1, friendNumber: %2)")
        .arg(Enums::toString(connectionStatus))
        .arg(friendNumber);
}
} // namespace Events
