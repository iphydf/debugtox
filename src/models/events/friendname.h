#pragma once

#include "src/models/bytes/bytearray.h"
#include "src/models/coreevent.h"

#include <cstdint>

class QString;
struct Tox_Event_Friend_Name;

namespace Events {
class FriendName final : public CoreEvent
{
public:
    explicit FriendName(const Tox_Event_Friend_Name* event);
    ~FriendName() override;
    QString toString() const override;

    const ByteArray name;
    const uint32_t friendNumber;
};
} // namespace Events
