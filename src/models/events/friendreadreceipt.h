#pragma once

#include "src/models/coreevent.h"

#include <cstdint>

class QString;
struct Tox_Event_Friend_Read_Receipt;

namespace Events {
class FriendReadReceipt final : public CoreEvent
{
public:
    explicit FriendReadReceipt(const Tox_Event_Friend_Read_Receipt* event);
    ~FriendReadReceipt() override;
    QString toString() const override;

    const uint32_t friendNumber;
    const uint32_t messageId;
};
} // namespace Events
