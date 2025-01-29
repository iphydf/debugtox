#include "groupvoicestate.h"

#include "src/models/enums/groupvoicestate_p.h"

#include <QString>

#include <tox/tox_events.h>

namespace Events {
GroupVoiceState::GroupVoiceState(const Tox_Event_Group_Voice_State* event)
    : groupNumber(tox_event_group_voice_state_get_group_number(event))
    , voiceState(Enums::fromTox(tox_event_group_voice_state_get_voice_state(event)))
{
}

GroupVoiceState::~GroupVoiceState() = default;

QString GroupVoiceState::toString() const
{
    return QStringLiteral("GroupVoiceState(groupNumber: %1, voiceState: %2)")
        .arg(groupNumber)
        .arg(Enums::toString(voiceState));
}
} // namespace Events
