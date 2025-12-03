#ifndef ICS_VECTOR_HPP
#define ICS_VECTOR_HPP

#include <iosfwd>    // For std::ostream
#include <cstddef>   // For size_t
#include <utility>   // For std::move
#include <stdexcept> // For std::ptrdiff_t in iterator difference
#include "vector_exception.hpp" // For VectorException

// Forward declarations of friend operators outside the class
template <typename T>
class Vector;

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vec);

template <typename T>
typename Vector<T>::Iterator operator+(size_t offset, const typename Vector<T>::Iterator& iter);

template <typename T>
typename Vector<T>::Iterator operator+(const typename Vector<T>::Iterator& iter, size_t offset);

template <typename T>
class Vector {
private:
    // Nested Iterator class
    class Iterator {
    private:
        Vector<T>* m_container;
        size_t index;
        
        // Constructor is private, only Vector can create Iterator instances
        Iterator(Vector<T>* container, size_t idx) 
            : m_container(container), index(idx) {}
        
        friend class Vector<T>; // Vector needs access to private constructor and members

    public:
        // Copy/Move operations are implicitly generated and should be fine

        // Pre-increment: ++it
        Iterator& operator++() {
            // Cannot increment past end()
            if (index >= m_container->m_size) {
                throw VectorException(m_container, "out of bounds");
            }
            ++index;
            return *this;
        }

        // Post-increment: it++
        Iterator operator++(int) {
            // Cannot increment past end()
            if (index >= m_container->m_size) {
                throw VectorException(m_container, "out of bounds");
            }
            Iterator temp = *this;
            ++index;
            return temp;
        }

        // Pre-decrement: --it
        Iterator& operator--() {
            // Cannot decrement from begin()
            if (index == 0) {
                throw VectorException(m_container, "out of bounds");
            }
            --index;
            return *this;
        }

        // Post-decrement: it--
        Iterator operator--(int) {
            // Cannot decrement from begin()
            if (index == 0) {
                throw VectorException(m_container, "out of bounds");
            }
            Iterator temp = *this;
            --index;
            return temp;
        }

        // Overloaded += operator
        Iterator& operator+=(size_t offset) {
            if (index + offset > m_container->m_size) {
                throw VectorException(m_container, "out of bounds");
            }
            index += offset;
            return *this;
        }

        // Overloaded -= operator
        Iterator& operator-=(size_t offset) {
            // check for underflow
            if (offset > index) {
                throw VectorException(m_container, "out of bounds");
            }
            index -= offset;
            return *this;
        }

        // Overloaded - operator (Iterator - Iterator)
        std::ptrdiff_t operator-(const Iterator& other) const {
            if (m_container != other.m_container) {
                throw VectorException(m_container, "iterators point to different containers");
            }
            // Use ptrdiff_t for difference, as specified by C++ standard for iterators
            return static_cast<std::ptrdiff_t>(index) - static_cast<std::ptrdiff_t>(other.index);
        }

        // Overloaded - operator (Iterator - size_t)
        Iterator operator-(size_t offset) const {
            // check for underflow
            if (offset > index) {
                throw VectorException(m_container, "out of bounds");
            }
            return Iterator(m_container, index - offset);
        }

        // Overloaded == operator
        bool operator==(const Iterator& other) const noexcept {
            // Iterators from different Vectors are always not equal
            return m_container == other.m_container && index == other.index;
        }

        // Overloaded != operator
        bool operator!=(const Iterator& other) const noexcept {
            return !(*this == other);
        }

        // Dereference operator: *it
        T& operator*() const {
            // Cannot dereference end() iterator (index == m_container->m_size)
            if (index >= m_container->m_size) {
                throw VectorException(m_container, "out of bounds");
            }
            return m_container->m_buffer[index];
        }

        // Arrow operator: it->member
        T* operator->() const {
            // Cannot dereference end() iterator
            if (index >= m_container->m_size) {
                throw VectorException(m_container, "out of bounds");
            }
            return &(m_container->m_buffer[index]);
        }

        // Friend operator+ declarations (Implemented outside the class)
        friend Vector<T>::Iterator operator+<T>(size_t offset, const Vector<T>::Iterator& iter);
        friend Vector<T>::Iterator operator+<T>(const Vector<T>::Iterator& iter, size_t offset);
    };

    // Private member fields
    size_t m_capacity;
    size_t m_size;
    T* m_buffer;

public:
    // Expose Iterator as a public type
    using Iterator = typename Vector<T>::Iterator;

    // --- Constructors and Destructor ---

    // Default constructor
    Vector() noexcept : m_capacity(0), m_size(0), m_buffer(nullptr) {}

    // Constructor with capacity
    Vector(size_t capacity) : m_capacity(capacity), m_size(0), m_buffer(nullptr) {
        if (capacity > 0) {
            // This is permitted by the guarantee that T is default constructible (new T[])
            m_buffer = new T[capacity];
        }
    }

    // Copy constructor
    Vector(const Vector& other) : m_capacity(other.m_capacity), m_size(other.m_size), m_buffer(nullptr) {
        if (m_capacity > 0) {
            m_buffer = new T[m_capacity];
            for (size_t i = 0; i < m_size; ++i) {
                // Use copy assignment/constructor
                m_buffer[i] = other.m_buffer[i];
            }
        }
    }

    // Copy assignment operator
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            // Self-assignment check
            
            // Clean up existing resources (explicit destruction not needed as delete[] will call destructors)
            delete[] m_buffer; 
            m_buffer = nullptr; // Reset to safe state
            
            m_capacity = other.m_capacity;
            m_size = other.m_size;

            if (m_capacity > 0) {
                m_buffer = new T[m_capacity];
                for (size_t i = 0; i < m_size; ++i) {
                    m_buffer[i] = other.m_buffer[i];
                }
            }
        }
        return *this;
    }

    // Move constructor
    Vector(Vector&& other) noexcept 
        : m_capacity(other.m_capacity), m_size(other.m_size), m_buffer(other.m_buffer) {
        // Leave the moved-from object in a valid, destructible state
        other.m_capacity = 0;
        other.m_size = 0;
        other.m_buffer = nullptr;
    }

    // Move assignment operator
    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            // Clean up existing resources before taking ownership
            delete[] m_buffer;

            m_capacity = other.m_capacity;
            m_size = other.m_size;
            m_buffer = other.m_buffer;

            // Leave the moved-from object in a valid, destructible state
            other.m_capacity = 0;
            other.m_size = 0;
            other.m_buffer = nullptr;
        }
        return *this;
    }

    // Destructor
    ~Vector() noexcept {
        delete[] m_buffer;
    }

    // --- Element Access and Info ---

    // begin()
    Iterator begin() noexcept {
        return Iterator(this, 0);
    }

    // begin() const
    T const * begin() const noexcept {
        // Return nullptr if empty as requested by the prompt
        return m_size > 0 ? m_buffer : nullptr;
    }

    // end()
    Iterator end() noexcept {
        // Points one past the last element (index == size)
        return Iterator(this, m_size);
    }

    // end() const
    T const * end() const noexcept {
        // Return nullptr if empty as requested by the prompt
        return m_size > 0 ? m_buffer + m_size : nullptr;
    }

    // front()
    T& front() noexcept {
        return m_buffer[0];
    }

    // front() const
    T const & front() const noexcept {
        return m_buffer[0];
    }

    // back()
    T& back() noexcept {
        return m_buffer[m_size - 1];
    }

    // back() const
    T const & back() const noexcept {
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
    T * data() noexcept {
        return m_buffer;
    }

    // data() const
    T const * data() const noexcept {
        return m_buffer;
    }

    // operator[]
    T& operator[](size_t index) noexcept {
        return m_buffer[index];
    }

    // operator[] const
    T const & operator[](size_t index) const noexcept {
        return m_buffer[index];
    }

    // at()
    T& at(size_t index) {
        if (index >= m_size) {
            throw VectorException(this, "out of bound");
        }
        return m_buffer[index];
    }

    // at() const
    T const & at(size_t index) const {
        if (index >= m_size) {
            throw VectorException(this, "out of bound");
        }
        return m_buffer[index];
    }

    // --- Modifiers ---

    // push_back(const T&)
    void push_back(const T& value) {
        if (m_size >= m_capacity) {
            size_t new_capacity = m_capacity == 0 ? 1 : m_capacity * 2;
            resize(new_capacity);
        }
        // Copy assignment for the new element
        m_buffer[m_size] = value;
        ++m_size;
    }

    // push_back(T&&)
    void push_back(T&& value) {
        if (m_size >= m_capacity) {
            size_t new_capacity = m_capacity == 0 ? 1 : m_capacity * 2;
            resize(new_capacity);
        }
        // Move assignment for the new element
        m_buffer[m_size] = std::move(value);
        ++m_size;
    }

    // pop_back()
    void pop_back() {
        if (m_size == 0) {
            throw VectorException(this, "popping from empty");
        }
        --m_size;
        // Explicitly call destructor for the last element
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
        
        // Move the elements after the erased range forward
        for (size_t i = end_idx; i < m_size; ++i) {
            m_buffer[start_idx + (i - end_idx)] = std::move(m_buffer[i]);
        }

        // Explicitly destroy the moved-from elements at the end of the buffer
        for (size_t i = m_size - count; i < m_size; ++i) {
            m_buffer[i].~T();
        }
        
        m_size -= count;
    }

    // swap_elements(lhs, rhs)
    void swap_elements(Iterator lhs, Iterator rhs) noexcept {
        // Use std::move to efficiently swap (will use T's move constructor/assignment)
        using std::swap;
        swap(m_buffer[lhs.index], m_buffer[rhs.index]);
    }

    // resize() - Changes capacity and size
    void resize(size_t new_capacity) {
        if (new_capacity == m_capacity) {
            return;
        }

        T* new_buffer = nullptr;
        if (new_capacity > 0) {
            new_buffer = new T[new_capacity];
        }

        size_t copy_size = m_size;
        if (new_capacity < m_size) {
            copy_size = new_capacity;
        }
        
        // Move elements to the new buffer
        for (size_t i = 0; i < copy_size; ++i) {
            // Move assignment/constructor is used here
            new_buffer[i] = std::move(m_buffer[i]);
            // Explicitly destroy the object in the old buffer (since it was moved-from)
            m_buffer[i].~T();
        }
        
        // Delete the old buffer (which calls destructors for remaining elements if copy_size < m_size)
        // Note: The logic for explicit destruction before delete[] can be complicated with new T[].
        // Relying on delete[] to call remaining destructors *after* manually destroying moved-from
        // elements is the cleanest approach given the constraints.
        delete[] m_buffer;

        m_buffer = new_buffer;
        m_capacity = new_capacity;
        m_size = copy_size; // m_size is truncated if new_capacity is smaller
    }

    // clear()
    void clear() noexcept {
        // Explicitly call destructor of every element
        for (size_t i = 0; i < m_size; ++i) {
            m_buffer[i].~T();
        }
        m_size = 0;
        // Capacity and buffer are unchanged
    }

    // --- Comparison Operators ---

    // operator==
    bool operator==(const Vector& other) const noexcept {
        if (m_size != other.m_size) {
            return false;
        }
        for (size_t i = 0; i < m_size; ++i) {
            // Note: relies on T::operator==
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

    // --- Friend Functions ---
    friend std::ostream& operator<< <T>(std::ostream& os, const Vector<T>& vec);
    friend Vector<T>::Iterator operator+ <T>(size_t offset, const Vector<T>::Iterator& iter);
    friend Vector<T>::Iterator operator+ <T>(const Vector<T>::Iterator& iter, size_t offset);
};

// Friend operator<< implementation
template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vec) {
    for (size_t i = 0; i < vec.m_size; ++i) {
        os << vec.m_buffer[i] << " ";
    }
    return os;
}

// Friend operator+ implementations
template <typename T>
typename Vector<T>::Iterator operator+(size_t offset, const typename Vector<T>::Iterator& iter) {
    typename Vector<T>::Iterator result(iter.m_container, iter.index + offset);
    if (result.index > result.m_container->m_size) {
        throw VectorException(result.m_container, "out of bounds");
    }
    return result;
}

template <typename T>
typename Vector<T>::Iterator operator+(const typename Vector<T>::Iterator& iter, size_t offset) {
    typename Vector<T>::Iterator result(iter.m_container, iter.index + offset);
    if (result.index > result.m_container->m_size) {
        throw VectorException(result.m_container, "out of bounds");
    }
    return result;
}

#endif