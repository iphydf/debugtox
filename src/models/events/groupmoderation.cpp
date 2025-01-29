#include "groupmoderation.h"

#include "src/models/enums/groupmodevent_p.h"

#include <QString>

#include <tox/tox_events.h>

namespace Events {
GroupModeration::GroupModeration(const Tox_Event_Group_Moderation* event)
    : groupNumber(tox_event_group_moderation_get_group_number(event))
    , sourcePeerId(tox_event_group_moderation_get_source_peer_id(event))
    , targetPeerId(tox_event_group_moderation_get_target_peer_id(event))
    , modType(Enums::fromTox(tox_event_group_moderation_get_mod_type(event)))
{
}

GroupModeration::~GroupModeration() = default;

QString GroupModeration::toString() const
{
    return QStringLiteral(
               "GroupModeration(groupNumber: %1, sourcePeerId: %2, targetPeerId: %3, modType: %4)")
        .arg(groupNumber)
        .arg(sourcePeerId)
        .arg(targetPeerId)
        .arg(Enums::toString(modType));
}
} // namespace Events
