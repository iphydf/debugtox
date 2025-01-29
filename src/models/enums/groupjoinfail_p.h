#pragma once

#include "groupjoinfail.h"

#include <tox/tox.h>

namespace Enums {
GroupJoinFail::Type fromTox(Tox_Group_Join_Fail value);
Tox_Group_Join_Fail toTox(GroupJoinFail::Type value);
} // namespace Enums
