#include "groupvoicestate_p.h"

#include <QMetaEnum>

#include <tox/tox.h>

GroupVoiceState::Type Enums::fromTox(Tox_Group_Voice_State value)
{
    switch (value) {
    case TOX_GROUP_VOICE_STATE_ALL:
        return GroupVoiceState::Type::ALL;
    case TOX_GROUP_VOICE_STATE_MODERATOR:
        return GroupVoiceState::Type::MODERATOR;
    case TOX_GROUP_VOICE_STATE_FOUNDER:
        return GroupVoiceState::Type::FOUNDER;
    }
    return GroupVoiceState::Type::ALL;
}
Tox_Group_Voice_State Enums::toTox(GroupVoiceState::Type value)
{
    switch (value) {
    case GroupVoiceState::Type::ALL:
        return TOX_GROUP_VOICE_STATE_ALL;
    case GroupVoiceState::Type::MODERATOR:
        return TOX_GROUP_VOICE_STATE_MODERATOR;
    case GroupVoiceState::Type::FOUNDER:
        return TOX_GROUP_VOICE_STATE_FOUNDER;
    }
    return TOX_GROUP_VOICE_STATE_ALL;
}

QString Enums::toString(GroupVoiceState::Type value)
{
    return QString::fromUtf8(
        QMetaEnum::fromType<GroupVoiceState::Type>().valueToKey(static_cast<int>(value)));
}
