#include "groupprivacystate.h"

#include "src/models/enums/groupprivacystate_p.h"

#include <QString>

#include <tox/tox_events.h>

namespace Events {
GroupPrivacyState::GroupPrivacyState(const Tox_Event_Group_Privacy_State* event)
    : groupNumber(tox_event_group_privacy_state_get_group_number(event))
    , privacyState(Enums::fromTox(tox_event_group_privacy_state_get_privacy_state(event)))
{
}

GroupPrivacyState::~GroupPrivacyState() = default;

QString GroupPrivacyState::toString() const
{
    return QStringLiteral("GroupPrivacyState(groupNumber: %1, privacyState: %2)")
        .arg(groupNumber)
        .arg(Enums::toString(privacyState));
}
} // namespace Events
