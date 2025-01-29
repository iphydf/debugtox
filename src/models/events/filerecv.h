#pragma once

#include "src/models/bytes/bytearray.h"
#include "src/models/coreevent.h"

#include <cstdint>

class QString;
struct Tox_Event_File_Recv;

namespace Events {
class FileRecv final : public CoreEvent
{
public:
    explicit FileRecv(const Tox_Event_File_Recv* event);
    ~FileRecv() override;
    QString toString() const override;

    const ByteArray filename;
    const uint32_t fileNumber;
    const uint64_t fileSize;
    const uint32_t friendNumber;
    const uint32_t kind;
};
} // namespace Events
