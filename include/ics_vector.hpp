#ifndef ICS_VECTOR_HPP
#define ICS_VECTOR_HPP

#include <iosfwd>
#include <cstddef>
#include <utility>
#include <new>
#include "vector_exception.hpp"

template <typename T>
class Vector {
private:
    // Nested Iterator class
    class Iterator {
    private:
        Vector<T>* m_container;
        size_t index;
        
        friend class Vector<T>;

    public:
        // Constructor
        Iterator(Vector<T>* container, size_t idx) 
            : m_container(container), index(idx) {}

        // Pre-increment
        Iterator& operator++() {
            if (index >= m_container->m_size) {
                throw VectorException("out of bounds");
            }
            ++index;
            return *this;
        }

        // Post-increment
        Iterator operator++(int) {
            if (index >= m_container->m_size) {
                throw VectorException("out of bounds");
            }
            Iterator temp = *this;
            ++index;
            return temp;
        }

        // Pre-decrement
        Iterator& operator--() {
            if (index == 0) {
                throw VectorException("out of bounds");
            }
            --index;
            return *this;
        }

        // Post-decrement
        Iterator operator--(int) {
            if (index == 0) {
                throw VectorException("out of bounds");
            }
            Iterator temp = *this;
            --index;
            return temp;
        }

        // Overloaded += operator
        Iterator& operator+=(size_t offset) {
            if (index + offset > m_container->m_size) {
                throw VectorException("out of bounds");
            }
            index += offset;
            return *this;
        }

        // Overloaded -= operator
        Iterator& operator-=(size_t offset) {
            if (offset > index) {
                throw VectorException("out of bounds");
            }
            index -= offset;
            return *this;
        }

        // Overloaded - operator (Iterator - Iterator)
        size_t operator-(const Iterator& other) const {
            if (m_container != other.m_container) {
                throw VectorException("iterators point to different containers");
            }
            return index - other.index;
        }

        // Overloaded - operator (Iterator - size_t)
        Iterator operator-(size_t offset) const {
            if (offset > index) {
                throw VectorException("out of bounds");
            }
            Iterator temp = *this;
            temp.index -= offset;
            return temp;
        }

        // Overloaded == operator
        bool operator==(const Iterator& other) const noexcept {
            return m_container == other.m_container && index == other.index;
        }

        // Overloaded != operator
        bool operator!=(const Iterator& other) const noexcept {
            return m_container != other.m_container || index != other.index;
        }

        // Dereference operator
        T& operator*() const {
            if (index >= m_container->m_size) {
                throw VectorException("out of bounds");
            }
            return m_container->m_buffer[index];
        }

        // Arrow operator
        T* operator->() const {
            if (index >= m_container->m_size) {
                throw VectorException("out of bounds");
            }
            return &(m_container->m_buffer[index]);
        }

        // Friend operator+ implementations inline
        friend Iterator operator+(size_t offset, const Iterator& iter) {
            Iterator result(iter.m_container, iter.index + offset);
            if (result.index > result.m_container->m_size) {
                throw VectorException("out of bounds");
            }
            return result;
        }
        
        friend Iterator operator+(const Iterator& iter, size_t offset) {
            Iterator result(iter.m_container, iter.index + offset);
            if (result.index > result.m_container->m_size) {
                throw VectorException("out of bounds");
            }
            return result;
        }
    };

    // Private member fields
    size_t m_capacity;
    size_t m_size;
    T* m_buffer;

    // Helper to get raw memory
    T* allocate(size_t n) {
        if (n == 0) return nullptr;
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    // Helper to free raw memory
    void deallocate(T* ptr) {
        ::operator delete(ptr);
    }

public:
    // Default constructor
    Vector() noexcept : m_capacity(0), m_size(0), m_buffer(nullptr) {}

    // Constructor with capacity
    Vector(size_t capacity) : m_capacity(capacity), m_size(0), m_buffer(nullptr) {
        if (capacity > 0) {
            m_buffer = allocate(capacity);
        }
    }

    // Copy constructor
    Vector(const Vector& other) : m_capacity(other.m_capacity), m_size(0), m_buffer(nullptr) {
        if (m_capacity > 0) {
            m_buffer = allocate(m_capacity);
            for (size_t i = 0; i < other.m_size; ++i) {
                new (&m_buffer[i]) T(other.m_buffer[i]);
                ++m_size;
            }
        }
    }

    // Copy assignment operator
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

    // Move constructor
    Vector(Vector&& other) noexcept 
        : m_capacity(other.m_capacity), m_size(other.m_size), m_buffer(other.m_buffer) {
        other.m_capacity = 0;
        other.m_size = 0;
        other.m_buffer = nullptr;
    }

    // Move assignment operator
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

    // Destructor
    ~Vector() noexcept {
        for (size_t i = 0; i < m_size; ++i) {
            m_buffer[i].~T();
        }
        deallocate(m_buffer);
    }

    // begin() - returns Iterator
    Iterator begin() noexcept {
        return Iterator(this, 0);
    }

    // begin() const - returns const T*
    const T* begin() const noexcept {
        return m_size > 0 ? m_buffer : nullptr;
    }

    // end() - returns Iterator
    Iterator end() noexcept {
        return Iterator(this, m_size);
    }

    // end() const - returns const T*
    const T* end() const noexcept {
        return m_size > 0 ? m_buffer + m_size : nullptr;
    }

    // front()
    T& front() noexcept {
        return m_buffer[0];
    }

    // front() const
    const T& front() const noexcept {
        return m_buffer[0];
    }

    // back()
    T& back() noexcept {
        return m_buffer[m_size - 1];
    }

    // back() const
    const T& back() const noexcept {
        return m_buffer[m_size - 1];
    }

    // empty()
    bool empty() const noexcept {
        return m_size == 0;
    }

    // size()
    size_t size() const noexcept {
        return m_size;
    }

    // capacity()
    size_t capacity() const noexcept {
        return m_capacity;
    }

    // data()
    T* data() noexcept {
        return m_buffer;
    }

    // data() const
    const T* data() const noexcept {
        return m_buffer;
    }

    // push_back(const T&)
    void push_back(const T& value) {
        if (m_size >= m_capacity) {
            size_t new_capacity = m_capacity == 0 ? 1 : m_capacity * 2;
            resize(new_capacity);
        }
        new (&m_buffer[m_size]) T(value);
        ++m_size;
    }

    // push_back(T&&)
    void push_back(T&& value) {
        if (m_size >= m_capacity) {
            size_t new_capacity = m_capacity == 0 ? 1 : m_capacity * 2;
            resize(new_capacity);
        }
        new (&m_buffer[m_size]) T(std::move(value));
        ++m_size;
    }

    // pop_back()
    void pop_back() {
        if (m_size == 0) {
            throw VectorException("popping from empty");
        }
        --m_size;
        m_buffer[m_size].~T();
    }

    // erase(start, end)
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

    // swap_elements(lhs, rhs)
    void swap_elements(Iterator lhs, Iterator rhs) noexcept {
        T temp = std::move(m_buffer[lhs.index]);
        m_buffer[lhs.index] = std::move(m_buffer[rhs.index]);
        m_buffer[rhs.index] = std::move(temp);
    }

    // operator[]
    T& operator[](size_t index) noexcept {
        return m_buffer[index];
    }

    // operator[] const
    const T& operator[](size_t index) const noexcept {
        return m_buffer[index];
    }

    // at()
    T& at(size_t index) {
        if (index >= m_size) {
            throw VectorException("out of bounds");
        }
        return m_buffer[index];
    }

    // at() const
    const T& at(size_t index) const {
        if (index >= m_size) {
            throw VectorException("out of bounds");
        }
        return m_buffer[index];
    }

    // operator==
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

    // operator!=
    bool operator!=(const Vector& other) const noexcept {
        return !(*this == other);
    }

    // resize()
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

    // clear()
    void clear() noexcept {
        for (size_t i = 0; i < m_size; ++i) {
            m_buffer[i].~T();
        }
        m_size = 0;
    }

    // operator
    friend std::ostream& operator<<(std::ostream& os, const Vector& vec) {
        for (size_t i = 0; i < vec.m_size; ++i) {
            os << vec.m_buffer[i] << " ";
        }
        return os;
    }
};

#endif
