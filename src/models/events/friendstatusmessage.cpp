#include "friendstatusmessage.h"

#include <QString>

#include <tox/tox_events.h>

namespace Events {
FriendStatusMessage::FriendStatusMessage(const Tox_Event_Friend_Status_Message* event)
    : message(tox_event_friend_status_message_get_message(event),
              tox_event_friend_status_message_get_message_length(event))
    , friendNumber(tox_event_friend_status_message_get_friend_number(event))
{
}

FriendStatusMessage::~FriendStatusMessage() = default;

QString FriendStatusMessage::toString() const
{
    return QStringLiteral("FriendStatusMessage(message: %1, friendNumber: %2)")
        .arg(message.toString())
        .arg(friendNumber);
}
} // namespace Events
