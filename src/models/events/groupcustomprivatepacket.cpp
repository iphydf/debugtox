#include "groupcustomprivatepacket.h"

#include <QString>

#include <tox/tox_events.h>

namespace Events {
GroupCustomPrivatePacket::GroupCustomPrivatePacket(const Tox_Event_Group_Custom_Private_Packet* event)
    : groupNumber(tox_event_group_custom_private_packet_get_group_number(event))
    , peerId(tox_event_group_custom_private_packet_get_peer_id(event))
    , data(tox_event_group_custom_private_packet_get_data(event),
           tox_event_group_custom_private_packet_get_data_length(event))
{
}

GroupCustomPrivatePacket::~GroupCustomPrivatePacket() = default;

QString GroupCustomPrivatePacket::toString() const
{
    return QStringLiteral("GroupCustomPrivatePacket(groupNumber: %1, peerId: %2, data: %3)")
        .arg(groupNumber)
        .arg(peerId)
        .arg(data.toString());
}
} // namespace Events
