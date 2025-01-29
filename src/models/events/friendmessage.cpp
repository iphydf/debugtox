#include "friendmessage.h"

#include "src/models/enums/messagetype_p.h"

#include <QString>

#include <tox/tox_events.h>

namespace Events {
FriendMessage::FriendMessage(const Tox_Event_Friend_Message* event)
    : friendNumber(tox_event_friend_message_get_friend_number(event))
    , type(Enums::fromTox(tox_event_friend_message_get_type(event)))
    , message(tox_event_friend_message_get_message(event),
              tox_event_friend_message_get_message_length(event))
{
}

FriendMessage::~FriendMessage() = default;

QString FriendMessage::toString() const
{
    return QStringLiteral("FriendMessage(friendNumber: %1, type: %2, message: %3)")
        .arg(friendNumber)
        .arg(Enums::toString(type))
        .arg(message.toString());
}
} // namespace Events
