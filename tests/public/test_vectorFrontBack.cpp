#include <ics_vector.hpp>
#include <catch_amalgamated.hpp>

namespace {
    // there's not much to test here.
    // just need to test that the code does not crash
    TEST_CASE("HW 6 Vector Front on Empty", "[vector-front-back]") {
        Vector<int> x;
        CHECK_NOTHROW(x.front());
        static_assert(noexcept(x.front()));
    }

    TEST_CASE("HW 6 Vector Front on One Element", "[vector-front-back]") {
        Vector<int> x;
        x.push_back(42);
        CHECK(x.front() == 42);
    }

    TEST_CASE("HW 6 Vector const Front on One Element", "[vector-front-back]") {
        Vector<int> x;
        x.push_back(42);
        const auto y = x;
        CHECK(y.front() == 42);
    }

    TEST_CASE("HW 6 Vector Front on Two Elements", "[vector-front-back]") {
        Vector<int> x;
        x.push_back(42);
        x.push_back(84);
        CHECK(x.front() == 42);
    }

    TEST_CASE("HW 6 Vector Back on empty", "[vector-front-back]") {
        Vector<int> x;
        x.back();
    }

    TEST_CASE("HW 6 Vector Back on one element", "[vector-front-back]") {
        Vector<int> x;
        x.push_back(24);
        CHECK(x.back() == 24);
    }

    TEST_CASE("HW 6 Vector Back on two elements", "[vector-front-back]") {
        Vector<int> x;
        x.push_back(24);
        x.push_back(48);
        CHECK(x.back() == 48);
        static_assert(noexcept(x.back()));
    }

    TEST_CASE("HW 6 Vector const Back on two elements", "[vector-front-back]") {
        Vector<int> x;
        x.push_back(24);
        x.push_back(48);

        const auto y = x;
        CHECK(y.back() == 48);
    }

}
