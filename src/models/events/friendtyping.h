#pragma once

#include "src/models/coreevent.h"

#include <cstdint>

class QString;
struct Tox_Event_Friend_Typing;

namespace Events {
class FriendTyping final : public CoreEvent
{
public:
    explicit FriendTyping(const Tox_Event_Friend_Typing* event);
    ~FriendTyping() override;
    QString toString() const override;

    const uint32_t friendNumber;
    const bool typing;
};
} // namespace Events
