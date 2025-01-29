#pragma once

#include "src/models/enums/groupprivacystate.h"
#include "src/models/coreevent.h"

#include <cstdint>

class QString;
struct Tox_Event_Group_Privacy_State;

namespace Events {
class GroupPrivacyState final : public CoreEvent
{
public:
    explicit GroupPrivacyState(const Tox_Event_Group_Privacy_State* event);
    ~GroupPrivacyState() override;
    QString toString() const override;

    const uint32_t groupNumber;
    const ::GroupPrivacyState::Type privacyState;
};
} // namespace Events
