#include "filerecv.h"

#include <QString>

#include <tox/tox_events.h>

namespace Events {
FileRecv::FileRecv(const Tox_Event_File_Recv* event)
    : filename(tox_event_file_recv_get_filename(event), tox_event_file_recv_get_filename_length(event))
    , fileNumber(tox_event_file_recv_get_file_number(event))
    , fileSize(tox_event_file_recv_get_file_size(event))
    , friendNumber(tox_event_file_recv_get_friend_number(event))
    , kind(tox_event_file_recv_get_kind(event))
{
}

FileRecv::~FileRecv() = default;

QString FileRecv::toString() const
{
    return QStringLiteral(
               "FileRecv(filename: %1, fileNumber: %2, fileSize: %3, friendNumber: %4, kind: %5)")
        .arg(filename.toString())
        .arg(fileNumber)
        .arg(fileSize)
        .arg(friendNumber)
        .arg(kind);
}
} // namespace Events
