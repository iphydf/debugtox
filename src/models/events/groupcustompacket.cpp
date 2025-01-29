#include "groupcustompacket.h"

#include <QString>

#include <tox/tox_events.h>

namespace Events {
GroupCustomPacket::GroupCustomPacket(const Tox_Event_Group_Custom_Packet* event)
    : groupNumber(tox_event_group_custom_packet_get_group_number(event))
    , peerId(tox_event_group_custom_packet_get_peer_id(event))
    , data(tox_event_group_custom_packet_get_data(event),
           tox_event_group_custom_packet_get_data_length(event))
{
}

GroupCustomPacket::~GroupCustomPacket() = default;

QString GroupCustomPacket::toString() const
{
    return QStringLiteral("GroupCustomPacket(groupNumber: %1, peerId: %2, data: %3)")
        .arg(groupNumber)
        .arg(peerId)
        .arg(data.toString());
}
} // namespace Events
