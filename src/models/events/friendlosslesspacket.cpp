#include "friendlosslesspacket.h"

#include <QString>

#include <tox/tox_events.h>

namespace Events {
FriendLosslessPacket::FriendLosslessPacket(const Tox_Event_Friend_Lossless_Packet* event)
    : data(tox_event_friend_lossless_packet_get_data(event),
           tox_event_friend_lossless_packet_get_data_length(event))
    , friendNumber(tox_event_friend_lossless_packet_get_friend_number(event))
{
}

FriendLosslessPacket::~FriendLosslessPacket() = default;

QString FriendLosslessPacket::toString() const
{
    return QStringLiteral("FriendLosslessPacket(data: %1, friendNumber: %2)")
        .arg(data.toString())
        .arg(friendNumber);
}
} // namespace Events
