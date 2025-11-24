
#include <catch_amalgamated.hpp>
#include <ics_vector.hpp>

namespace {
    TEST_CASE("HW 6 empty always equals empty", "[vec-equality]") {
        Vector<int> x;

        CHECK(x == Vector<int>{});
        CHECK_FALSE(x != Vector<int>{});
    }

    TEST_CASE("HW 6 vectors equal themselves", "[vec-equality]") {
        Vector<int> x;
        for (auto n : {0, 1, 2, 3, 4}) {
            CHECK(x == x);
            CHECK_FALSE(x != x);
            x.push_back(n);
        }

        CHECK(x == x);
        CHECK_FALSE(x != x);
    }

    TEST_CASE("HW 6 different vectors are different", "[vec-equality]") {
        Vector<int> x, y;
        for (auto n : {0, 1, 2, 3, 4}) {
            x.push_back(n);
            y.push_back(n + 1);
        }

        CHECK(x != y);
        CHECK_FALSE(x == y);
    }

    TEST_CASE("HW 6 different capacities do not matter", "[vec-equality]") {
        Vector<int> x, y{10};
        for (auto n : {0, 1, 2, 3, 4}) {
            x.push_back(n);
            y.push_back(n);
        }

        CHECK_FALSE(x.capacity() == y.capacity());
        CHECK(x == y);
    }

    TEST_CASE("HW 6 equality only needs ==", "[vec-equality]") {
        struct Eq {
            int x;
            Eq() : x{0} {}
            Eq(int x): x{x} {}
            
            bool operator==(const Eq & lhs) const {
                return this->x == lhs.x;
            }
        };

        Vector<int> x, y{10};
        for (auto n : {0, 1, 2, 3, 4}) {
            x.push_back(n);
            y.push_back(n);
        }

        CHECK_FALSE(x.capacity() == y.capacity());
        CHECK(x == y);
    }
} // namespace
