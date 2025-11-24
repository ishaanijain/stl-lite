# HW06: C++ Template Programming

The Integrated Computer Systems 45 Corporation (ICS45C) wants to write a library for use in its lightweight devices.
Since they like object-oriented programming and high performance code, they have chosen C++ as their only language.
They have tried using other libraries, but none were what they needed.

Since vectors (resizing arrays) are very common, they need an implementation in their ICS45C library.
They want to store many different types in these vectors without suffering any loss in performance or ergonomics,
so it must be a template.
Note that due to many files have large include blocks, the team wants a file that can be included multiple times and still compile.

It is your job as the newly-hired intern on the team to implement it using as few external dependencies as possible, since this will be deployed on very small devices.
For the convenience of printing out the vector, you are allowed `iosfwd` to get `std::ostream`.
They already have a exception class specifically for vectors in `vector_exception.hpp`, but little else.
Note that `VectorException` needs both the `Vector` that caused the exception and a message.
So in total, there should only be two includes in `ics_vector.hpp`.

Since the data structure is rather complex, a coworker has written a lot of tests for you.
These are all public and there will be no extra tests for the foreseeable future.

## Implementing Vector<T> 

A vector can grow and shrink in size at runtime and support constant-time random access. It's most similar to Python's `list` datatype.

The `T` is the templated `typename` that the user of the `Vector` specifies to say what it contains. 
E.g., `Vector<int>` means that `int` will be stored in the array.
Because the vector will be used with many different types, there are a few properties of `T` that we can guarantee.
1. it can be default constructed (i.e., `T{}` and `T()` compile) for `new T[]`
2. it is moveable and `std::move` works on it
3. `==` works always and `!=` may not exist

`Vector<T>` should only include the following private member fields:
- A capacity of `size_t`
- A size of `size_t`
- A pointer to a buffer of `T` (should be `T*`)

Note that capacity and size are different. Size refers to how many items are currently in the `Vector<T>` while capacity is the maximum size before requiring a buffer resize to accomodate future insertions.

For enhanced type safety, as many functions as possible should be marked `noexcept` and `const` to tell the caller that no exceptions are thrown and that the current value is not modified, respectively.
A main source of exceptions is allocation, as every time `new` is used, it may throw due to not finding enough memory.

### `Vector<T>` should include

- A constructor that does not take any parameters and initializes the vector size to 0 and capacity to 0
- An overloaded constructor that takes only `size_t` for capacity that allocates a buffer to that capacity. Note that it does not initialize any values.
- A copy constructor that will create a copy from another `Vector<T>`
- A copy assignment operator that clears the current `this` buffer and initializes it to be a copy from another `Vector<T>`
- A move constructor that moves from another `Vector<T>`. Should be `noexcept`
- A move assignment operator that moves all variables from another `Vector<T>`. Should be `noexcept`
- A destructor that deallocates the underlying buffer. Should be `noexcept`

`Vector<T>` should include the following member functions:
- `Iterator begin() noexcept` should return the iterator to the first element (see iterator description)
- `T const * begin() const noexcept` should return a const pointer to the first element or `nullptr` if no such element exists
- `Iterator end() noexcept` should return the iterator to the spot right after the last element
- `T const * end() const noexcept` should return a pointer to the spot right after the last element or `nullptr` if no such element exists
- `T & front() noexcept` should return a reference to the first element
- `T const & front() const noexcept` should return a reference to the first element
- `T & back() noexcept` should return a reference to the last element
- `T const & back() const noexcept` should return a reference to the last element
- `bool empty() const noexcept` should return a boolean which represents whether or not the vector is empty
- `size_t size() const noexcept` should return the size of the vector
- `size_t capacity() const noexcept` should return the capacity of the underlying buffer
- `T * data() noexcept` should return a pointer of type `T*` to the underlying buffer
- `T const * data() const noexcept` should returns a pointer of type `const T*` to the underlying buffer
- `void push_back(const T&)` appends an item onto the vector, resizing to twice the initial capacity or 1 whichever is larger
- `void push_back(T&&)` appends an item onto the vector, resizing to twice the initial capacity or 1 whichever is larger. This version of `push_back` must `std::move` the item
- `void pop_back()` removes and destroys the last item of the vector, throwing an exception if no item exists. The exception message should be "popping from empty".
- `void erase(start, end)` removes the range between the `start` and `end` iterators provided. If `start == end`, no items should be erased. It should only modify size. Assume that `start <= end`
- `void swap_elements(lhs, rhs) noexcept` swaps the items pointed at by the two iterators provided using `std::move`.
- `T & operator[](size_t index) noexcept` returns a reference to the item at the provided index. For performance reasons, there is no bounds check.
- `T const & operator[](size_t index) const noexcept` returns a const reference to the item at the provided index. For performance reasons, there is no bounds check.
- `T & at(size_t index)` returns a reference to the item at the provided index, throwing an exception if the index is out of range. The exception message should be "out of bound"
- `T const & at(size_t index) const` returns a reference to the item at the provided index, throwing an exception if the index is out of range. The exception message should be "out of bound"
- `void resize(size_t new_capacity)` changes the capacity and size of the vector to the specified new capacity, efficiently moving the items to the new buffer and cleaning up the old one. Note that 
1. if the requested capacity is the existing capacity return immediately.
2. it can make the size of the vector smaller, but not larger
- `bool operator==(const Vector &) const noexcept` overloaded equality returns true when the size of the vectors are the same and the contents of their buffers are the same. The capacities do not need to be the same.
- `bool operator!=(const Vector &) const noexcept` overloaded inequality returns true when the size of the vectors are different or the contents of their buffers are different. The capacities do not need to be the same.
- `void clear() noexcept` calls the destructor of every element within the vector and sets the vector size to 0. Note that it does not change the capacity or reallocate the buffer
- `friend operator<<(std::ostream&, const Vector&)` prints out the vector using the provided ostream and forwards that ostream along.

The following code should print "2 1 0 " (each item followed by a single space):
```
Vector<int> x;
x.push_back(2);
x.push_back(1);
x.push_back(0);
std::cout << x << std::endl;
```

Some `Vector<T>` operations will return an `Iterator`, which needs to be a inner private class.
This prevents anyone outside of `Vector` from creating random iterators to nowhere.
Iterators are like pointers, but can be implemented with a little more safety in mind.

### `Vector<T>::Iterator` class should support
- `Iterator & operator++` pre-increment, throwing an exception if called on the `end()` iterator. The exception message should be "out of bounds"
- `Iterator operator++` post-increment, throwing an exception if called on the `end()` iterator. The exception message should be "out of bounds"
- `Iterator & operator--` pre-decrement, throwing an exception if called on the `begin()` iterator. The exception message should be "out of bounds"
- `Iterator operator--` post-decrement, throwing an exception if called on the `begin()` iterator. The exception message should be "out of bounds"
- `bool operator==(const Iterator&) const noexcept` return true if two iterators are equal. Make sure that two iterators from *different* `Vector`s are always not equal
- `bool operator!=(const Iterator &) const noexcept` return true if two iterators are from different containers OR point to different indices.
- `T & operator*() const` dereferences the item at the current index. If the index is outside the bounds of the container, throw an exception. The exception message should be "out of bounds".
- `T * operator->() const` returns a pointer to the item at the current index. If the index is outside the bounds of the container, throw an exception. The exception message should be "out of bounds".
- `size_t operator-(const Iterator &) const` return the distance between two iterators, throwing an exception if the iterators come from different containers. The exception message should be "iterators point to different containers"
- `Iterator operator-(size_t offset) const` returns an iterator that is `offset` to the left as if by repeated pre-decrement on a copy of the current iterator
- `Iterator & operator+=(size_t) const` moves and returns this iterator forward as if by repeated pre-decrement on a copy of the current iterator
- `Iterator & operator-=(size_t) const` moves and returns this iterator back as if by repeated pre-decrement on a copy of the current iterator

The following friend functions allow arbitrary offsets on `Iterators` as if by repeated pre-increment on a copy of the provided iterator
- `friend Iterator operator+(size_t, const Iterator &)`
- `friend Iterator operator+(const Iterator &, size_t)`


Note that our iterators should support both the `for(auto & x : vector)` and the `for(auto iter = vector.begin(); iter != vector.end(); ++iter)` syntaxes.

#### Note on Special Member Functions
Since the `Iterator` class is private, we cannot test the constructor of it, but we recommend that one is written.
There need not be a destructor, as iterators should behave similar to pointers.
Additionally, iterators should be copyable and moveable.


## Submission Notes
You only need to complete `include/ics_vector.hpp`.

All tests have been provided for you; there are no private ones.