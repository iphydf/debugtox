#include "publickey.h"

#include <QByteArray>
#include <QString>

#include <algorithm>
#include <array>

namespace {
template <size_t N>
std::array<uint8_t, N> fromPointer(const uint8_t* data)
{
    std::array<uint8_t, N> result;
    std::copy(data, data + N, result.begin());
    return result;
}
} // namespace

PublicKey::PublicKey(const uint8_t* data)
    : data(fromPointer<32>(data))
{
}

PublicKey::~PublicKey() = default;

QString PublicKey::toString() const
{
    return QString::fromUtf8(
        QByteArray(reinterpret_cast<const char*>(data.data()), data.size()).toHex());
}
