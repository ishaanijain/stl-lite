#include <ics_vector.hpp>
#include <catch_amalgamated.hpp>

namespace {
    // there's not much to test here.
    // just need to test that the code does not crash
    TEST_CASE("HW 6 Vector Empty() on Empty", "[vector-empty]") {
        Vector<int> x;
        CHECK(x.empty());
        static_assert(noexcept(x.empty()));
    }

    TEST_CASE("HW 6 Vector Empty() on One Element", "[vector-empty]") {
        Vector<int> x;
        x.push_back(1);
        CHECK_FALSE(x.empty());
    }
}
