#pragma once

#include "src/models/enums/connection.h"
#include "src/models/coreevent.h"

class QString;
struct Tox_Event_Self_Connection_Status;

namespace Events {
class SelfConnectionStatus final : public CoreEvent
{
public:
    explicit SelfConnectionStatus(const Tox_Event_Self_Connection_Status* event);
    ~SelfConnectionStatus() override;
    QString toString() const override;

    const ::Connection::Type connectionStatus;
};
} // namespace Events
