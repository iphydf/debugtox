#include "friendreadreceipt.h"

#include <QString>

#include <tox/tox_events.h>

namespace Events {
FriendReadReceipt::FriendReadReceipt(const Tox_Event_Friend_Read_Receipt* event)
    : friendNumber(tox_event_friend_read_receipt_get_friend_number(event))
    , messageId(tox_event_friend_read_receipt_get_message_id(event))
{
}

FriendReadReceipt::~FriendReadReceipt() = default;

QString FriendReadReceipt::toString() const
{
    return QStringLiteral("FriendReadReceipt(friendNumber: %1, messageId: %2)").arg(friendNumber).arg(messageId);
}
} // namespace Events
