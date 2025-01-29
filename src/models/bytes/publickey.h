#pragma once

#include <array>

class QString;

struct PublicKey final
{
    explicit PublicKey(const uint8_t* data);
    ~PublicKey();
    QString toString() const;

    const std::array<uint8_t, 32> data;
};
