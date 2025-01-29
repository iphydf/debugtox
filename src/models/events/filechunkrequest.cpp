#include "filechunkrequest.h"

#include <QString>

#include <tox/tox_events.h>

namespace Events {
FileChunkRequest::FileChunkRequest(const Tox_Event_File_Chunk_Request* event)
    : length(tox_event_file_chunk_request_get_length(event))
    , fileNumber(tox_event_file_chunk_request_get_file_number(event))
    , friendNumber(tox_event_file_chunk_request_get_friend_number(event))
    , position(tox_event_file_chunk_request_get_position(event))
{
}

FileChunkRequest::~FileChunkRequest() = default;

QString FileChunkRequest::toString() const
{
    return QStringLiteral(
               "FileChunkRequest(length: %1, fileNumber: %2, friendNumber: %3, position: %4)")
        .arg(length)
        .arg(fileNumber)
        .arg(friendNumber)
        .arg(position);
}
} // namespace Events
