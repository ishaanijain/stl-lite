#include "ics_vector.hpp"

#include <catch_amalgamated.hpp>

// Test correct behavior (no-throwing)
// tests vector capacity and vector size
namespace {
    // Capacity tests.
    TEST_CASE("HW 6 Vector Capacity Constructor Test", "[vectorgrowth]") {
        Vector<int> vec(6);
        CHECK(vec.capacity() == 6);
    }

    TEST_CASE("HW 6 Vector Capacity Doubling from 0 Test", "[vectorgrowth]") {
        // Capacity doubling test.
        Vector<int> vec;
        CHECK(vec.capacity() == 0);
        vec.push_back(5);
        CHECK(vec.capacity() == 1);
        vec.push_back(5);
        CHECK(vec.capacity() == 2);
        vec.push_back(5);
        CHECK(vec.capacity() == 4);
        CHECK(vec.size() == 3);
    }

    TEST_CASE("HW 6 Vector Capacity Doubling the Provided Test", "[vectorgrowth]") {
        static constexpr auto initial = 6;
        Vector<int> vec(initial);
        CHECK(vec.capacity() == initial);

        for (auto n : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) vec.push_back(n);

        CHECK(vec.capacity() == 2 * initial);
    }
} // namespace
