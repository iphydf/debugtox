#pragma once

#include "userstatus.h"

#include <tox/tox.h>

namespace Enums {
UserStatus::Type fromTox(Tox_User_Status value);
Tox_User_Status toTox(UserStatus::Type value);
} // namespace Enums
