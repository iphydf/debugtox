#include "conferencetitle.h"

#include <QString>

#include <tox/tox_events.h>

namespace Events {
ConferenceTitle::ConferenceTitle(const Tox_Event_Conference_Title* event)
    : title(tox_event_conference_title_get_title(event),
            tox_event_conference_title_get_title_length(event))
    , conferenceNumber(tox_event_conference_title_get_conference_number(event))
    , peerNumber(tox_event_conference_title_get_peer_number(event))
{
}

ConferenceTitle::~ConferenceTitle() = default;

QString ConferenceTitle::toString() const
{
    return QStringLiteral("ConferenceTitle(title: %1, conferenceNumber: %2, peerNumber: %3)")
        .arg(title.toString())
        .arg(conferenceNumber)
        .arg(peerNumber);
}
} // namespace Events
