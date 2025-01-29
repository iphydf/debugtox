#include "messagetype_p.h"

#include <QMetaEnum>

#include <tox/tox.h>

MessageType::Type Enums::fromTox(Tox_Message_Type value)
{
    switch (value) {
    case TOX_MESSAGE_TYPE_NORMAL:
        return MessageType::Type::NORMAL;
    case TOX_MESSAGE_TYPE_ACTION:
        return MessageType::Type::ACTION;
    }
    return MessageType::Type::NORMAL;
}
Tox_Message_Type Enums::toTox(MessageType::Type value)
{
    switch (value) {
    case MessageType::Type::NORMAL:
        return TOX_MESSAGE_TYPE_NORMAL;
    case MessageType::Type::ACTION:
        return TOX_MESSAGE_TYPE_ACTION;
    }
    return TOX_MESSAGE_TYPE_NORMAL;
}

QString Enums::toString(MessageType::Type value)
{
    return QString::fromUtf8(
        QMetaEnum::fromType<MessageType::Type>().valueToKey(static_cast<int>(value)));
}
