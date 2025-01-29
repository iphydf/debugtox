#include "grouppeerexit.h"

#include "src/models/enums/groupexittype_p.h"

#include <QString>

#include <tox/tox_events.h>

namespace Events {
GroupPeerExit::GroupPeerExit(const Tox_Event_Group_Peer_Exit* event)
    : groupNumber(tox_event_group_peer_exit_get_group_number(event))
    , peerId(tox_event_group_peer_exit_get_peer_id(event))
    , exitType(Enums::fromTox(tox_event_group_peer_exit_get_exit_type(event)))
    , name(tox_event_group_peer_exit_get_name(event), tox_event_group_peer_exit_get_name_length(event))
    , partMessage(tox_event_group_peer_exit_get_part_message(event),
                  tox_event_group_peer_exit_get_part_message_length(event))
{
}

GroupPeerExit::~GroupPeerExit() = default;

QString GroupPeerExit::toString() const
{
    return QStringLiteral("GroupPeerExit(groupNumber: %1, peerId: %2, exitType: %3, name: %4, "
                          "partMessage: %5)")
        .arg(groupNumber)
        .arg(peerId)
        .arg(Enums::toString(exitType))
        .arg(name.toString())
        .arg(partMessage.toString());
}
} // namespace Events
