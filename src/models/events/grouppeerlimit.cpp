#include "grouppeerlimit.h"

#include <QString>

#include <tox/tox_events.h>

namespace Events {
GroupPeerLimit::GroupPeerLimit(const Tox_Event_Group_Peer_Limit* event)
    : groupNumber(tox_event_group_peer_limit_get_group_number(event))
    , peerLimit(tox_event_group_peer_limit_get_peer_limit(event))
{
}

GroupPeerLimit::~GroupPeerLimit() = default;

QString GroupPeerLimit::toString() const
{
    return QStringLiteral("GroupPeerLimit(groupNumber: %1, peerLimit: %2)").arg(groupNumber).arg(peerLimit);
}
} // namespace Events
