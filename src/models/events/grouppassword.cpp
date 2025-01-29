#include "grouppassword.h"

#include <QString>

#include <tox/tox_events.h>

namespace Events {
GroupPassword::GroupPassword(const Tox_Event_Group_Password* event)
    : groupNumber(tox_event_group_password_get_group_number(event))
    , password(tox_event_group_password_get_password(event),
               tox_event_group_password_get_password_length(event))
{
}

GroupPassword::~GroupPassword() = default;

QString GroupPassword::toString() const
{
    return QStringLiteral("GroupPassword(groupNumber: %1, password: %2)")
        .arg(groupNumber)
        .arg(password.toString());
}
} // namespace Events
