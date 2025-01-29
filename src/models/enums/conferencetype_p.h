#pragma once

#include "conferencetype.h"

#include <tox/tox.h>

namespace Enums {
ConferenceType::Type fromTox(Tox_Conference_Type value);
Tox_Conference_Type toTox(ConferenceType::Type value);
} // namespace ConferenceType
