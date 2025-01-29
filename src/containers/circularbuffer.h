#pragma once

#include <QList>

#include <cstddef>
#include <deque>

template <typename T>
class CircularBuffer
{
public:
    explicit CircularBuffer(std::size_t capacity)
        : m_capacity(capacity)
    {
    }

    void push(const T& value)
    {
        if (m_buffer.size() == m_capacity) {
            m_buffer.pop_front();
        }
        m_buffer.push_back(value);
    }

    std::size_t size() const
    {
        return m_buffer.size();
    }

    std::size_t capacity() const
    {
        return m_capacity;
    }

    T& operator[](std::size_t index)
    {
        return m_buffer.at(index);
    }

    const T& operator[](std::size_t index) const
    {
        return m_buffer.at(index);
    }

    QList<T> toList() const
    {
        return QList<T>(m_buffer.begin(), m_buffer.end());
    }

    void resize(std::size_t size)
    {
        if (size < m_buffer.size()) {
            m_buffer.resize(size);
        }
        m_capacity = size;
    }

private:
    std::deque<T> m_buffer;
    std::size_t m_capacity;
};
