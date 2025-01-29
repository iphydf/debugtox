#pragma once

#include "src/models/bytes/bytearray.h"
#include "src/models/coreevent.h"

#include <cstdint>

class QString;
struct Tox_Event_Group_Topic;

namespace Events {
class GroupTopic final : public CoreEvent
{
public:
    explicit GroupTopic(const Tox_Event_Group_Topic* event);
    ~GroupTopic() override;
    QString toString() const override;

    const uint32_t groupNumber;
    const uint32_t peerId;
    const ByteArray topic;
};
} // namespace Events
