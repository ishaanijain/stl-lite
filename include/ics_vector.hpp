#ifndef ICS_VECTOR_HPP
#define ICS_VECTOR_HPP

#include <iosfwd>
#include <cstddef>
#include <utility>
#include "vector_exception.hpp"

template <typename T>
class Vector {
private:
    class Iterator {
    private:
        Vector<T>* m_container;
        size_t index;
        
        friend class Vector<T>;

    public:
        Iterator(Vector<T>* container, size_t idx) 
            : m_container(container), index(idx) {}

        Iterator& operator++() {
            if (index >= m_container->m_size) {
                throw VectorException("out of bounds");
            }
            ++index;
            return *this;
        }

        Iterator operator++(int) {
            if (index >= m_container->m_size) {
                throw VectorException("out of bounds");
            }
            Iterator temp = *this;
            ++index;
            return temp;
        }

        Iterator& operator--() {
            if (index == 0) {
                throw VectorException("out of bounds");
            }
            --index;
            return *this;
        }

        Iterator operator--(int) {
            if (index == 0) {
                throw VectorException("out of bounds");
            }
            Iterator temp = *this;
            --index;
            return temp;
        }

        Iterator& operator+=(size_t offset) {
            if (index + offset > m_container->m_size) {
                throw VectorException("out of bounds");
            }
            index += offset;
            return *this;
        }

        Iterator& operator-=(size_t offset) {
            if (offset > index) {
                throw VectorException("out of bounds");
            }
            index -= offset;
            return *this;
        }

        size_t operator-(const Iterator& other) const {
            if (m_container != other.m_container) {
                throw VectorException("iterators point to different containers");
            }
            return index - other.index;
        }

        Iterator operator-(size_t offset) const {
            if (offset > index) {
                throw VectorException("out of bounds");
            }
            Iterator temp = *this;
            temp.index -= offset;
            return temp;
        }

        bool operator==(const Iterator& other) const noexcept {
            return m_container == other.m_container && index == other.index;
        }

        bool operator!=(const Iterator& other) const noexcept {
            return m_container != other.m_container || index != other.index;
        }

        T& operator*() const {
            if (index >= m_container->m_size) {
                throw VectorException("out of bounds");
            }
            return m_container->m_buffer[index];
        }

        T* operator->() const {
            if (index >= m_container->m_size) {
                throw VectorException("out of bounds");
            }
            return &(m_container->m_buffer[index]);
        }

        Iterator operator+(size_t offset) const {
            Iterator result(m_container, index + offset);
            if (result.index > m_container->m_size) {
                throw VectorException("out of bounds");
            }
            return result;
        }
    };

    size_t m_capacity;
    size_t m_size;
    T* m_buffer;

    T* allocate(size_t n) {
        if (n == 0) return nullptr;
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    void deallocate(T* ptr) {
        ::operator delete(ptr);
    }

public:
    Vector() noexcept : m_capacity(0), m_size(0), m_buffer(nullptr) {}

    Vector(size_t capacity) : m_capacity(capacity), m_size(0), m_buffer(nullptr) {
        if (capacity > 0) {
            m_buffer = allocate(capacity);
        }
    }

    Vector(const Vector& other) : m_capacity(other.m_capacity), m_size(0), m_buffer(nullptr) {
        if (m_capacity > 0) {
            m_buffer = allocate(m_capacity);
            for (size_t i = 0; i < other.m_size; ++i) {
                new (&m_buffer[i]) T(other.m_buffer[i]);
                ++m_size;
            }
        }
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            for (size_t i = 0; i < m_size; ++i) {
                m_buffer[i].~T();
            }
            deallocate(m_buffer);
            
            m_capacity = other.m_capacity;
            m_size = 0;
            if (m_capacity > 0) {
                m_buffer = allocate(m_capacity);
                for (size_t i = 0; i < other.m_size; ++i) {
                    new (&m_buffer[i]) T(other.m_buffer[i]);
                    ++m_size;
                }
            } else {
                m_buffer = nullptr;
            }
        }
        return *this;
    }

    Vector(Vector&& other) noexcept 
        : m_capacity(other.m_capacity), m_size(other.m_size), m_buffer(other.m_buffer) {
        other.m_capacity = 0;
        other.m_size = 0;
        other.m_buffer = nullptr;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            for (size_t i = 0; i < m_size; ++i) {
                m_buffer[i].~T();
            }
            deallocate(m_buffer);
            
            m_capacity = other.m_capacity;
            m_size = other.m_size;
            m_buffer = other.m_buffer;
            other.m_capacity = 0;
            other.m_size = 0;
            other.m_buffer = nullptr;
        }
        return *this;
    }

    ~Vector() noexcept {
        for (size_t i = 0; i < m_size; ++i) {
            m_buffer[i].~T();
        }
        deallocate(m_buffer);
    }

    Iterator begin() noexcept {
        return Iterator(this, 0);
    }

    const T* begin() const noexcept {
        return m_size > 0 ? m_buffer : nullptr;
    }

    Iterator end() noexcept {
        return Iterator(this, m_size);
    }

    const T* end() const noexcept {
        return m_size > 0 ? m_buffer + m_size : nullptr;
    }

    T& front() noexcept {
        return m_buffer[0];
    }

    const T& front() const noexcept {
        return m_buffer[0];
    }

    T& back() noexcept {
        return m_buffer[m_size - 1];
    }

    const T& back() const noexcept {
        return m_buffer[m_size - 1];
    }

    bool empty() const noexcept {
        return m_size == 0;
    }

    size_t size() const noexcept {
        return m_size;
    }

    size_t capacity() const noexcept {
        return m_capacity;
    }

    T* data() noexcept {
        return m_buffer;
    }

    const T* data() const noexcept {
        return m_buffer;
    }

    void push_back(const T& value) {
        if (m_size >= m_capacity) {
            size_t new_capacity = m_capacity == 0 ? 1 : m_capacity * 2;
            resize(new_capacity);
        }
        new (&m_buffer[m_size]) T(value);
        ++m_size;
    }

    void push_back(T&& value) {
        if (m_size >= m_capacity) {
            size_t new_capacity = m_capacity == 0 ? 1 : m_capacity * 2;
            resize(new_capacity);
        }
        new (&m_buffer[m_size]) T(std::move(value));
        ++m_size;
    }

    void pop_back() {
        if (m_size == 0) {
            throw VectorException("popping from empty");
        }
        --m_size;
        m_buffer[m_size].~T();
    }

    void erase(Iterator start, Iterator end) {
        if (start == end) {
            return;
        }
        size_t start_idx = start.index;
        size_t end_idx = end.index;
        size_t count = end_idx - start_idx;
        
        for (size_t i = end_idx; i < m_size; ++i) {
            m_buffer[start_idx + (i - end_idx)] = std::move(m_buffer[i]);
        }
        
        for (size_t i = m_size - count; i < m_size; ++i) {
            m_buffer[i].~T();
        }
        
        m_size -= count;
    }

    void swap_elements(Iterator lhs, Iterator rhs) noexcept {
        T temp = std::move(m_buffer[lhs.index]);
        m_buffer[lhs.index] = std::move(m_buffer[rhs.index]);
        m_buffer[rhs.index] = std::move(temp);
    }

    T& operator[](size_t index) noexcept {
        return m_buffer[index];
    }

    const T& operator[](size_t index) const noexcept {
        return m_buffer[index];
    }

    T& at(size_t index) {
        if (index >= m_size) {
            throw VectorException("out of bounds");
        }
        return m_buffer[index];
    }

    const T& at(size_t index) const {
        if (index >= m_size) {
            throw VectorException("out of bounds");
        }
        return m_buffer[index];
    }

    bool operator==(const Vector& other) const noexcept {
        if (m_size != other.m_size) {
            return false;
        }
        for (size_t i = 0; i < m_size; ++i) {
            if (!(m_buffer[i] == other.m_buffer[i])) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Vector& other) const noexcept {
        return !(*this == other);
    }

    void resize(size_t new_capacity) {
        if (new_capacity == m_capacity) {
            return;
        }
        
        T* new_buffer = nullptr;
        if (new_capacity > 0) {
            new_buffer = allocate(new_capacity);
        }
        
        size_t copy_size = m_size < new_capacity ? m_size : new_capacity;
        
        for (size_t i = 0; i < copy_size; ++i) {
            new (&new_buffer[i]) T(std::move(m_buffer[i]));
        }
        
        for (size_t i = 0; i < m_size; ++i) {
            m_buffer[i].~T();
        }
        
        deallocate(m_buffer);
        m_buffer = new_buffer;
        m_capacity = new_capacity;
        
        if (m_size > new_capacity) {
            m_size = new_capacity;
        }
    }

    void clear() noexcept {
        for (size_t i = 0; i < m_size; ++i) {
            m_buffer[i].~T();
        }
        m_size = 0;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector& vec) {
        for (size_t i = 0; i < vec.m_size; ++i) {
            os << vec.m_buffer[i] << " ";
        }
        return os;
    }

    friend Iterator operator+(size_t offset, const Iterator& iter) {
        return iter + offset;
    }
};

#endif