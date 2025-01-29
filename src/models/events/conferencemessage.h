#pragma once

#include "src/models/bytes/bytearray.h"
#include "src/models/enums/messagetype.h"
#include "src/models/coreevent.h"

#include <cstdint>

class QString;
struct Tox_Event_Conference_Message;

namespace Events {
class ConferenceMessage final : public CoreEvent
{
public:
    explicit ConferenceMessage(const Tox_Event_Conference_Message* event);
    ~ConferenceMessage() override;
    QString toString() const override;

    const ByteArray message;
    const ::MessageType::Type type;
    const uint32_t conferenceNumber;
    const uint32_t peerNumber;
};
} // namespace Events
