#include "groupjoinfail.h"

#include "src/models/enums/groupjoinfail_p.h"

#include <QString>

#include <tox/tox_events.h>

namespace Events {
GroupJoinFail::GroupJoinFail(const Tox_Event_Group_Join_Fail* event)
    : groupNumber(tox_event_group_join_fail_get_group_number(event))
    , failType(Enums::fromTox(tox_event_group_join_fail_get_fail_type(event)))
{
}

GroupJoinFail::~GroupJoinFail() = default;

QString GroupJoinFail::toString() const
{
    return QStringLiteral("GroupJoinFail(groupNumber: %1, failType: %2)")
        .arg(groupNumber)
        .arg(Enums::toString(failType));
}
} // namespace Events
