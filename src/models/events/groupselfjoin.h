#pragma once

#include "src/models/coreevent.h"

#include <cstdint>

class QString;
struct Tox_Event_Group_Self_Join;

namespace Events {
class GroupSelfJoin final : public CoreEvent
{
public:
    explicit GroupSelfJoin(const Tox_Event_Group_Self_Join* event);
    ~GroupSelfJoin() override;
    QString toString() const override;

    const uint32_t groupNumber;
};
} // namespace Events
