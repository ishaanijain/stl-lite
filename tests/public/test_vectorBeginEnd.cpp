#include <catch_amalgamated.hpp>
#include <ics_vector.hpp>
#include <ics_vector.hpp>

namespace {
    // there's not much to test here.
    // just need to test that the code does not crash
    TEST_CASE("HW 6 Vector Begin on Empty", "[vector-begin-end]") {
        Vector<int> x;
        CHECK_NOTHROW(x.begin());
        static_assert(noexcept(x.begin()));
    }

    TEST_CASE("HW 6 Vector Begin on One Element", "[vector-begin-end]") {
        Vector<int> x;
        x.push_back(42);
        CHECK(*x.begin() == 42);
    }

    TEST_CASE("HW 6 Vector Begin on Two Elements", "[vector-begin-end]") {
        Vector<int> x;
        x.push_back(42);
        x.push_back(84);
        CHECK(*x.begin() == 42);
    }

    TEST_CASE("HW 6 Vector Begin on Const Vector", "[vector-begin-end]") {
        Vector<int> x;
        x.push_back(30);
        x.push_back(25);

        const Vector<int> y = x;
        const int* frnt = y.begin();

        CHECK(*frnt == 30);
    }

    TEST_CASE("HW 6 Vector End on empty", "[vector-begin-end]") {
        Vector<int> x;
        CHECK_NOTHROW(x.end());
        static_assert(noexcept(x.end()));
    }

    TEST_CASE("HW 6 Vector End on one element", "[vector-begin-end]") {
        Vector<int> x;
        x.push_back(24);
        CHECK_NOTHROW(x.end());
    }
    
    TEST_CASE("HW 6 Vector End on Const Vector", "[vector-begin-end]") {
        Vector<int> x;
        x.push_back(30);
        x.push_back(25);
        const Vector<int> y = x;
        CHECK_NOTHROW(y.end());
    }
} // namespace
