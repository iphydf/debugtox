#include "filerecvcontrol.h"

#include "src/models/enums/filecontrol_p.h"

#include <QString>

#include <tox/tox_events.h>

namespace Events {
FileRecvControl::FileRecvControl(const Tox_Event_File_Recv_Control* event)
    : control(Enums::fromTox(tox_event_file_recv_control_get_control(event)))
    , fileNumber(tox_event_file_recv_control_get_file_number(event))
    , friendNumber(tox_event_file_recv_control_get_friend_number(event))
{
}

FileRecvControl::~FileRecvControl() = default;

QString FileRecvControl::toString() const
{
    return QStringLiteral("FileRecvControl(control: %1, fileNumber: %2, friendNumber: %3)")
        .arg(Enums::toString(control))
        .arg(fileNumber)
        .arg(friendNumber);
}
} // namespace Events
