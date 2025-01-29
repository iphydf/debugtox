#pragma once

#include "src/models/bytes/bytearray.h"
#include "src/models/coreevent.h"

#include <cstdint>

class QString;
struct Tox_Event_Group_Password;

namespace Events {
class GroupPassword final : public CoreEvent
{
public:
    explicit GroupPassword(const Tox_Event_Group_Password* event);
    ~GroupPassword() override;
    QString toString() const override;

    const uint32_t groupNumber;
    const ByteArray password;
};
} // namespace Events
