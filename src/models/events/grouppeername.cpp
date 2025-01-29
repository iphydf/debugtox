#include "grouppeername.h"

#include <QString>

#include <tox/tox_events.h>

namespace Events {
GroupPeerName::GroupPeerName(const Tox_Event_Group_Peer_Name* event)
    : groupNumber(tox_event_group_peer_name_get_group_number(event))
    , peerId(tox_event_group_peer_name_get_peer_id(event))
    , name(tox_event_group_peer_name_get_name(event), tox_event_group_peer_name_get_name_length(event))
{
}

GroupPeerName::~GroupPeerName() = default;

QString GroupPeerName::toString() const
{
    return QStringLiteral("GroupPeerName(groupNumber: %1, peerId: %2, name: %3)")
        .arg(groupNumber)
        .arg(peerId)
        .arg(name.toString());
}
} // namespace Events
