#pragma once

#include "groupvoicestate.h"

#include <tox/tox.h>

namespace Enums {
GroupVoiceState::Type fromTox(Tox_Group_Voice_State value);
Tox_Group_Voice_State toTox(GroupVoiceState::Type value);
} // namespace Enums
