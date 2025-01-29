#pragma once

#include "src/models/bytes/bytearray.h"
#include "src/models/enums/messagetype.h"
#include "src/models/coreevent.h"

#include <cstdint>

class QString;
struct Tox_Event_Friend_Message;

namespace Events {
class FriendMessage final : public CoreEvent
{
public:
    explicit FriendMessage(const Tox_Event_Friend_Message* event);
    ~FriendMessage() override;
    QString toString() const override;

    const uint32_t friendNumber;
    const ::MessageType::Type type;
    const ByteArray message;
};
} // namespace Events
