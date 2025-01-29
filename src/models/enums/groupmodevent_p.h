#pragma once

#include "groupmodevent.h"

#include <tox/tox.h>

namespace Enums {
GroupModEvent::Type fromTox(Tox_Group_Mod_Event value);
Tox_Group_Mod_Event toTox(GroupModEvent::Type value);
} // namespace Enums
