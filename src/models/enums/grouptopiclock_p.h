#pragma once

#include "grouptopiclock.h"

#include <tox/tox.h>

namespace Enums {
GroupTopicLock::Type fromTox(Tox_Group_Topic_Lock value);
Tox_Group_Topic_Lock toTox(GroupTopicLock::Type value);
} // namespace Enums
