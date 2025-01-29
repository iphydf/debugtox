#pragma once

#include "src/models/coreevent.h"

#include <cstdint>

class QString;
struct Tox_Event_File_Chunk_Request;

namespace Events {
class FileChunkRequest final : public CoreEvent
{
public:
    explicit FileChunkRequest(const Tox_Event_File_Chunk_Request* event);
    ~FileChunkRequest() override;
    QString toString() const override;

    const uint16_t length;
    const uint32_t fileNumber;
    const uint32_t friendNumber;
    const uint64_t position;
};
} // namespace Events
