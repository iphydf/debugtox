#include "groupinvite.h"

#include <QString>

#include <tox/tox_events.h>

namespace Events {
GroupInvite::GroupInvite(const Tox_Event_Group_Invite* event)
    : friendNumber(tox_event_group_invite_get_friend_number(event))
    , inviteData(tox_event_group_invite_get_invite_data(event),
                 tox_event_group_invite_get_invite_data_length(event))
    , groupName(tox_event_group_invite_get_group_name(event),
                tox_event_group_invite_get_group_name_length(event))
{
}

GroupInvite::~GroupInvite() = default;

QString GroupInvite::toString() const
{
    return QStringLiteral("GroupInvite(friendNumber: %1, inviteData: %2, groupName: %3)")
        .arg(friendNumber)
        .arg(inviteData.toString())
        .arg(groupName.toString());
}
} // namespace Events
