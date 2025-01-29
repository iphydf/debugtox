#include "grouppeerstatus.h"

#include "src/models/enums/userstatus_p.h"

#include <QString>

#include <tox/tox_events.h>

namespace Events {
GroupPeerStatus::GroupPeerStatus(const Tox_Event_Group_Peer_Status* event)
    : groupNumber(tox_event_group_peer_status_get_group_number(event))
    , peerId(tox_event_group_peer_status_get_peer_id(event))
    , status(Enums::fromTox(tox_event_group_peer_status_get_status(event)))
{
}

GroupPeerStatus::~GroupPeerStatus() = default;

QString GroupPeerStatus::toString() const
{
    return QStringLiteral("GroupPeerStatus(groupNumber: %1, peerId: %2, status: %3)")
        .arg(groupNumber)
        .arg(peerId)
        .arg(Enums::toString(status));
}
} // namespace Events
