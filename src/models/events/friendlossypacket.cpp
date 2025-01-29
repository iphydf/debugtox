#include "friendlossypacket.h"

#include <QString>

#include <tox/tox_events.h>

namespace Events {
FriendLossyPacket::FriendLossyPacket(const Tox_Event_Friend_Lossy_Packet* event)
    : data(tox_event_friend_lossy_packet_get_data(event),
           tox_event_friend_lossy_packet_get_data_length(event))
    , friendNumber(tox_event_friend_lossy_packet_get_friend_number(event))
{
}

FriendLossyPacket::~FriendLossyPacket() = default;

QString FriendLossyPacket::toString() const
{
    return QStringLiteral("FriendLossyPacket(data: %1, friendNumber: %2)").arg(data.toString()).arg(friendNumber);
}
} // namespace Events
