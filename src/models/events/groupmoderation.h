#pragma once

#include "src/models/enums/groupmodevent.h"
#include "src/models/coreevent.h"

#include <cstdint>

class QString;
struct Tox_Event_Group_Moderation;

namespace Events {
class GroupModeration final : public CoreEvent
{
public:
    explicit GroupModeration(const Tox_Event_Group_Moderation* event);
    ~GroupModeration() override;
    QString toString() const override;

    const uint32_t groupNumber;
    const uint32_t sourcePeerId;
    const uint32_t targetPeerId;
    const ::GroupModEvent::Type modType;
};
} // namespace Events
