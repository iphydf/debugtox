#pragma once

#include "groupexittype.h"

#include <tox/tox.h>

namespace Enums {
GroupExitType::Type fromTox(Tox_Group_Exit_Type value);
Tox_Group_Exit_Type toTox(GroupExitType::Type value);
} // namespace Enums
