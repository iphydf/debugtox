#include "friendrequest.h"

#include <QString>

#include <tox/tox_events.h>

namespace Events {
FriendRequest::FriendRequest(const Tox_Event_Friend_Request* event)
    : message(tox_event_friend_request_get_message(event),
              tox_event_friend_request_get_message_length(event))
    , publicKey(tox_event_friend_request_get_public_key(event))
{
}

FriendRequest::~FriendRequest() = default;

QString FriendRequest::toString() const
{
    return QStringLiteral("FriendRequest(message: %1, publicKey: %2)")
        .arg(message.toString())
        .arg(publicKey.toString());
}
} // namespace Events
