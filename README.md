# stl-lite

A lightweight, header-only implementation of a dynamic array (vector) in C++. Built from scratch to understand the internals of STL containers, memory management, and modern C++ patterns.

## Features

- **Template-based** — works with any default-constructible, moveable type
- **STL-compatible iterators** — supports range-based for loops and standard iterator patterns
- **Exception-safe** — proper bounds checking with `at()`, safe `pop_back()`
- **Move semantics** — efficient transfers with move constructor/assignment
- **Minimal dependencies** — only requires `<iosfwd>` for stream output

## Usage
```cpp
#include "ics_vector.hpp"

Vector<int> v;
v.push_back(1);
v.push_back(2);
v.push_back(3);

for (auto& x : v) {
    std::cout << x << " ";
}
// Output: 1 2 3
```

## API Overview

| Method | Description |
|--------|-------------|
| `push_back(item)` | Append element (copy or move) |
| `pop_back()` | Remove last element |
| `at(index)` | Bounds-checked access |
| `operator[]` | Fast unchecked access |
| `size()` / `capacity()` | Current size and buffer capacity |
| `resize(n)` | Change capacity |
| `clear()` | Remove all elements |
| `begin()` / `end()` | Iterator support |

## Building

Header-only — just include `ics_vector.hpp` in your project.

To run tests:
```bash
mkdir build && cd build
cmake ..
make
./tests
```

## License

MIT
