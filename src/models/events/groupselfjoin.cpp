#include "groupselfjoin.h"

#include <QString>

#include <tox/tox_events.h>

namespace Events {
GroupSelfJoin::GroupSelfJoin(const Tox_Event_Group_Self_Join* event)
    : groupNumber(tox_event_group_self_join_get_group_number(event))
{
}

GroupSelfJoin::~GroupSelfJoin() = default;

QString GroupSelfJoin::toString() const
{
    return QStringLiteral("GroupSelfJoin(groupNumber: %1)").arg(groupNumber);
}
} // namespace Events
