#include "conferenceinvite.h"

#include "src/models/enums/conferencetype_p.h"

#include <QString>

#include <tox/tox_events.h>

namespace Events {
ConferenceInvite::ConferenceInvite(const Tox_Event_Conference_Invite* event)
    : cookie(tox_event_conference_invite_get_cookie(event),
             tox_event_conference_invite_get_cookie_length(event))
    , type(Enums::fromTox(tox_event_conference_invite_get_type(event)))
    , friendNumber(tox_event_conference_invite_get_friend_number(event))
{
}

ConferenceInvite::~ConferenceInvite() = default;

QString ConferenceInvite::toString() const
{
    return QStringLiteral("ConferenceInvite(cookie: %1, type: %2, friendNumber: %3)")
        .arg(cookie.toString())
        .arg(Enums::toString(type))
        .arg(friendNumber);
}
} // namespace Events
