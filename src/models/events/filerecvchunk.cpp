#include "filerecvchunk.h"

#include <QString>

#include <tox/tox_events.h>

namespace Events {
FileRecvChunk::FileRecvChunk(const Tox_Event_File_Recv_Chunk* event)
    : data(tox_event_file_recv_chunk_get_data(event), tox_event_file_recv_chunk_get_data_length(event))
    , fileNumber(tox_event_file_recv_chunk_get_file_number(event))
    , friendNumber(tox_event_file_recv_chunk_get_friend_number(event))
    , position(tox_event_file_recv_chunk_get_position(event))
{
}

FileRecvChunk::~FileRecvChunk() = default;

QString FileRecvChunk::toString() const
{
    return QStringLiteral("FileRecvChunk(data: %1, fileNumber: %2, friendNumber: %3, position: %4)")
        .arg(data.toString())
        .arg(fileNumber)
        .arg(friendNumber)
        .arg(position);
}
} // namespace Events
