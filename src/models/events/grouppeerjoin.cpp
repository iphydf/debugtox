#include "grouppeerjoin.h"

#include <QString>

#include <tox/tox_events.h>

namespace Events {
GroupPeerJoin::GroupPeerJoin(const Tox_Event_Group_Peer_Join* event)
    : groupNumber(tox_event_group_peer_join_get_group_number(event))
    , peerId(tox_event_group_peer_join_get_peer_id(event))
{
}

GroupPeerJoin::~GroupPeerJoin() = default;

QString GroupPeerJoin::toString() const
{
    return QStringLiteral("GroupPeerJoin(groupNumber: %1, peerId: %2)").arg(groupNumber).arg(peerId);
}
} // namespace Events
