#pragma once

#include "filecontrol.h"

#include <tox/tox.h>

namespace Enums {
FileControl::Type fromTox(Tox_File_Control value);
Tox_File_Control toTox(FileControl::Type value);
} // namespace Enums
