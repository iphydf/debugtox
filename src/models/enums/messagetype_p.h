#pragma once

#include "messagetype.h"

#include <tox/tox.h>

namespace Enums {
MessageType::Type fromTox(Tox_Message_Type value);
Tox_Message_Type toTox(MessageType::Type value);
} // namespace Enums
