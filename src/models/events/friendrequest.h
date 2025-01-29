#pragma once

#include "src/models/bytes/bytearray.h"
#include "src/models/bytes/publickey.h"
#include "src/models/coreevent.h"

class QString;
struct Tox_Event_Friend_Request;

namespace Events {
class FriendRequest final : public CoreEvent
{
public:
    explicit FriendRequest(const Tox_Event_Friend_Request* event);
    ~FriendRequest() override;
    QString toString() const override;

    const ByteArray message;
    const PublicKey publicKey;
};
} // namespace Events
