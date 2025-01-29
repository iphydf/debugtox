#pragma once

#include "src/models/bytes/bytearray.h"
#include "src/models/bytes/publickey.h"
#include "src/models/coreevent.h"

#include <cstdint>

class QString;
struct Tox_Event_Dht_Get_Nodes_Response;

namespace Events {
class DhtGetNodesResponse final : public CoreEvent
{
public:
    explicit DhtGetNodesResponse(const Tox_Event_Dht_Get_Nodes_Response* event);
    ~DhtGetNodesResponse() override;
    QString toString() const override;

    const PublicKey publicKey;
    const ByteArray ip;
    const uint16_t port;
};
} // namespace Events
