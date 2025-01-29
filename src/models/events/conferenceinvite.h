#pragma once

#include "src/models/bytes/bytearray.h"
#include "src/models/enums/conferencetype.h"
#include "src/models/coreevent.h"

#include <cstdint>

class QString;
struct Tox_Event_Conference_Invite;

namespace Events {
class ConferenceInvite final : public CoreEvent
{
public:
    explicit ConferenceInvite(const Tox_Event_Conference_Invite* event);
    ~ConferenceInvite() override;
    QString toString() const override;

    const ByteArray cookie;
    const ::ConferenceType::Type type;
    const uint32_t friendNumber;
};
} // namespace Events
