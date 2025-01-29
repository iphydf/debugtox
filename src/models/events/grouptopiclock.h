#pragma once

#include "src/models/enums/grouptopiclock.h"
#include "src/models/coreevent.h"

#include <cstdint>

class QString;
struct Tox_Event_Group_Topic_Lock;

namespace Events {
class GroupTopicLock final : public CoreEvent
{
public:
    explicit GroupTopicLock(const Tox_Event_Group_Topic_Lock* event);
    ~GroupTopicLock() override;
    QString toString() const override;

    const uint32_t groupNumber;
    const ::GroupTopicLock::Type topicLock;
};
} // namespace Events
