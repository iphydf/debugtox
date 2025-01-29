#include "friendname.h"

#include <QString>

#include <tox/tox_events.h>

namespace Events {
FriendName::FriendName(const Tox_Event_Friend_Name* event)
    : name(tox_event_friend_name_get_name(event), tox_event_friend_name_get_name_length(event))
    , friendNumber(tox_event_friend_name_get_friend_number(event))
{
}

FriendName::~FriendName() = default;

QString FriendName::toString() const
{
    return QStringLiteral("FriendName(name: %1, friendNumber: %2)").arg(name.toString()).arg(friendNumber);
}
} // namespace Events
