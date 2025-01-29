#pragma once

#include "src/models/bytes/bytearray.h"
#include "src/models/coreevent.h"

#include <cstdint>

class QString;
struct Tox_Event_Conference_Title;

namespace Events {
class ConferenceTitle final : public CoreEvent
{
public:
    explicit ConferenceTitle(const Tox_Event_Conference_Title* event);
    ~ConferenceTitle() override;
    QString toString() const override;

    const ByteArray title;
    const uint32_t conferenceNumber;
    const uint32_t peerNumber;
};
} // namespace Events
