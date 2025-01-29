#pragma once

#include <memory>

class QString;
struct Tox_Event;

class CoreEvent
{
protected:
    CoreEvent();

public:
    virtual ~CoreEvent();

public:
    virtual QString toString() const = 0;

    static std::unique_ptr<CoreEvent> fromTox(const Tox_Event* event);
};
