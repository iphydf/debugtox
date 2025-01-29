#pragma once

#include "src/models/enums/filecontrol.h"
#include "src/models/coreevent.h"

#include <cstdint>

class QString;
struct Tox_Event_File_Recv_Control;

namespace Events {
class FileRecvControl final : public CoreEvent
{
public:
    explicit FileRecvControl(const Tox_Event_File_Recv_Control* event);
    ~FileRecvControl() override;
    QString toString() const override;

    const ::FileControl::Type control;
    const uint32_t fileNumber;
    const uint32_t friendNumber;
};
} // namespace Events
