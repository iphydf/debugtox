#include "filecontrol_p.h"

#include <QMetaEnum>

#include <tox/tox.h>

FileControl::Type Enums::fromTox(Tox_File_Control value)
{
    switch (value) {
    case TOX_FILE_CONTROL_RESUME:
        return FileControl::Type::RESUME;
    case TOX_FILE_CONTROL_PAUSE:
        return FileControl::Type::PAUSE;
    case TOX_FILE_CONTROL_CANCEL:
        return FileControl::Type::CANCEL;
    }
    return FileControl::Type::RESUME;
}
Tox_File_Control Enums::toTox(FileControl::Type value)
{
    switch (value) {
    case FileControl::Type::RESUME:
        return TOX_FILE_CONTROL_RESUME;
    case FileControl::Type::PAUSE:
        return TOX_FILE_CONTROL_PAUSE;
    case FileControl::Type::CANCEL:
        return TOX_FILE_CONTROL_CANCEL;
    }
    return TOX_FILE_CONTROL_RESUME;
}

QString Enums::toString(FileControl::Type value)
{
    return QString::fromUtf8(
        QMetaEnum::fromType<FileControl::Type>().valueToKey(static_cast<int>(value)));
}
