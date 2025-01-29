#pragma once

#include "src/models/coreevent.h"

#include <cstdint>

class QString;
struct Tox_Event_Conference_Peer_List_Changed;

namespace Events {
class ConferencePeerListChanged final : public CoreEvent
{
public:
    explicit ConferencePeerListChanged(const Tox_Event_Conference_Peer_List_Changed* event);
    ~ConferencePeerListChanged() override;
    QString toString() const override;

    const uint32_t conferenceNumber;
};
} // namespace Events
