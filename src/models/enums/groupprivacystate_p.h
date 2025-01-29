#pragma once

#include "groupprivacystate.h"

#include <tox/tox.h>

namespace Enums {
GroupPrivacyState::Type fromTox(Tox_Group_Privacy_State value);
Tox_Group_Privacy_State toTox(GroupPrivacyState::Type value);
} // namespace Enums
