#pragma once

#include "src/models/bytes/bytearray.h"
#include "src/models/coreevent.h"

#include <cstdint>

class QString;
struct Tox_Event_Friend_Status_Message;

namespace Events {
class FriendStatusMessage final : public CoreEvent
{
public:
    explicit FriendStatusMessage(const Tox_Event_Friend_Status_Message* event);
    ~FriendStatusMessage() override;
    QString toString() const override;

    const ByteArray message;
    const uint32_t friendNumber;
};
} // namespace Events
