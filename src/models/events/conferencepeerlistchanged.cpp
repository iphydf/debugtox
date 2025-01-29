#include "conferencepeerlistchanged.h"

#include <QString>

#include <tox/tox_events.h>

namespace Events {
ConferencePeerListChanged::ConferencePeerListChanged(const Tox_Event_Conference_Peer_List_Changed* event)
    : conferenceNumber(tox_event_conference_peer_list_changed_get_conference_number(event))
{
}

ConferencePeerListChanged::~ConferencePeerListChanged() = default;

QString ConferencePeerListChanged::toString() const
{
    return QStringLiteral("ConferencePeerListChanged(conferenceNumber: %1)").arg(conferenceNumber);
}
} // namespace Events
