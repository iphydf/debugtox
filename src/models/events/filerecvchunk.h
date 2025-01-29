#pragma once

#include "src/models/bytes/bytearray.h"
#include "src/models/coreevent.h"

#include <cstdint>

class QString;
struct Tox_Event_File_Recv_Chunk;

namespace Events {
class FileRecvChunk final : public CoreEvent
{
public:
    explicit FileRecvChunk(const Tox_Event_File_Recv_Chunk* event);
    ~FileRecvChunk() override;
    QString toString() const override;

    const ByteArray data;
    const uint32_t fileNumber;
    const uint32_t friendNumber;
    const uint64_t position;
};
} // namespace Events
