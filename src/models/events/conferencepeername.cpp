#include "conferencepeername.h"

#include <QString>

#include <tox/tox_events.h>

namespace Events {
ConferencePeerName::ConferencePeerName(const Tox_Event_Conference_Peer_Name* event)
    : name(tox_event_conference_peer_name_get_name(event),
           tox_event_conference_peer_name_get_name_length(event))
    , conferenceNumber(tox_event_conference_peer_name_get_conference_number(event))
    , peerNumber(tox_event_conference_peer_name_get_peer_number(event))
{
}

ConferencePeerName::~ConferencePeerName() = default;

QString ConferencePeerName::toString() const
{
    return QStringLiteral("ConferencePeerName(name: %1, conferenceNumber: %2, peerNumber: %3)")
        .arg(name.toString())
        .arg(conferenceNumber)
        .arg(peerNumber);
}
} // namespace Events
