#include "selfconnectionstatus.h"

#include "src/models/enums/connection_p.h"

#include <QString>

#include <tox/tox_events.h>

namespace Events {
SelfConnectionStatus::SelfConnectionStatus(const Tox_Event_Self_Connection_Status* event)
    : connectionStatus(Enums::fromTox(tox_event_self_connection_status_get_connection_status(event)))
{
}

SelfConnectionStatus::~SelfConnectionStatus() = default;

QString SelfConnectionStatus::toString() const
{
    return QStringLiteral("SelfConnectionStatus(connectionStatus: %1)")
        .arg(Enums::toString(connectionStatus));
}
} // namespace Events
