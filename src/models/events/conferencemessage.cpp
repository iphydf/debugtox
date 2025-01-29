#include "conferencemessage.h"

#include "src/models/enums/messagetype_p.h"

#include <QString>

#include <tox/tox_events.h>

namespace Events {
ConferenceMessage::ConferenceMessage(const Tox_Event_Conference_Message* event)
    : message(tox_event_conference_message_get_message(event),
              tox_event_conference_message_get_message_length(event))
    , type(Enums::fromTox(tox_event_conference_message_get_type(event)))
    , conferenceNumber(tox_event_conference_message_get_conference_number(event))
    , peerNumber(tox_event_conference_message_get_peer_number(event))
{
}

ConferenceMessage::~ConferenceMessage() = default;

QString ConferenceMessage::toString() const
{
    return QStringLiteral(
               "ConferenceMessage(message: %1, type: %2, conferenceNumber: %3, peerNumber: %4)")
        .arg(message.toString())
        .arg(Enums::toString(type))
        .arg(conferenceNumber)
        .arg(peerNumber);
}
} // namespace Events
