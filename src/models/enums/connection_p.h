#pragma once

#include "connection.h"

#include <tox/tox.h>

namespace Enums {
Connection::Type fromTox(Tox_Connection value);
Tox_Connection toTox(Connection::Type value);
} // namespace Enums
