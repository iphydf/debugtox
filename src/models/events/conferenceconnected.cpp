#include "conferenceconnected.h"

#include <QString>

#include <tox/tox_events.h>

namespace Events {
ConferenceConnected::ConferenceConnected(const Tox_Event_Conference_Connected* event)
    : conferenceNumber(tox_event_conference_connected_get_conference_number(event))
{
}

ConferenceConnected::~ConferenceConnected() = default;

QString ConferenceConnected::toString() const
{
    return QStringLiteral("ConferenceConnected(conferenceNumber: %1)").arg(conferenceNumber);
}
} // namespace Events
