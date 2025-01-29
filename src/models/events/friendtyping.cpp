#include "friendtyping.h"

#include <QString>

#include <tox/tox_events.h>

namespace Events {
FriendTyping::FriendTyping(const Tox_Event_Friend_Typing* event)
    : friendNumber(tox_event_friend_typing_get_friend_number(event))
    , typing(tox_event_friend_typing_get_typing(event))
{
}

FriendTyping::~FriendTyping() = default;

QString FriendTyping::toString() const
{
    return QStringLiteral("FriendTyping(friendNumber: %1, typing: %2)").arg(friendNumber).arg(typing);
}
} // namespace Events
