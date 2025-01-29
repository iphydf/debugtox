#pragma once

#include "src/models/enums/groupjoinfail.h"
#include "src/models/coreevent.h"

#include <cstdint>

class QString;
struct Tox_Event_Group_Join_Fail;

namespace Events {
class GroupJoinFail final : public CoreEvent
{
public:
    explicit GroupJoinFail(const Tox_Event_Group_Join_Fail* event);
    ~GroupJoinFail() override;
    QString toString() const override;

    const uint32_t groupNumber;
    const ::GroupJoinFail::Type failType;
};
} // namespace Events
