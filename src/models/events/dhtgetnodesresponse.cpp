#include "dhtgetnodesresponse.h"

#include <QString>

#include <tox/tox_events.h>

namespace Events {
DhtGetNodesResponse::DhtGetNodesResponse(const Tox_Event_Dht_Get_Nodes_Response* event)
    : publicKey(tox_event_dht_get_nodes_response_get_public_key(event))
    , ip(tox_event_dht_get_nodes_response_get_ip(event),
         tox_event_dht_get_nodes_response_get_ip_length(event))
    , port(tox_event_dht_get_nodes_response_get_port(event))
{
}

DhtGetNodesResponse::~DhtGetNodesResponse() = default;

QString DhtGetNodesResponse::toString() const
{
    return QStringLiteral("DhtGetNodesResponse(publicKey: %1, ip: %2, port: %3)")
        .arg(publicKey.toString())
        .arg(ip.toString())
        .arg(port);
}
} // namespace Events
