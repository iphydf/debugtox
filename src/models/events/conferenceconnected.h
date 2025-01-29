#pragma once

#include "src/models/coreevent.h"

#include <cstdint>

class QString;
struct Tox_Event_Conference_Connected;

namespace Events {
class ConferenceConnected final : public CoreEvent
{
public:
    explicit ConferenceConnected(const Tox_Event_Conference_Connected* event);
    ~ConferenceConnected() override;
    QString toString() const override;

    const uint32_t conferenceNumber;
};
} // namespace Events
