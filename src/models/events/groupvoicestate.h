#pragma once

#include "src/models/enums/groupvoicestate.h"
#include "src/models/coreevent.h"

#include <cstdint>

class QString;
struct Tox_Event_Group_Voice_State;

namespace Events {
class GroupVoiceState final : public CoreEvent
{
public:
    explicit GroupVoiceState(const Tox_Event_Group_Voice_State* event);
    ~GroupVoiceState() override;
    QString toString() const override;

    const uint32_t groupNumber;
    const ::GroupVoiceState::Type voiceState;
};
} // namespace Events
