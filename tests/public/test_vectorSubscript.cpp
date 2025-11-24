#include <ics_vector.hpp>
#include <catch_amalgamated.hpp>

namespace {
    TEST_CASE("HW 6 subscript ", "[vec-subscript]") {
        Vector<int> x;
        for (auto n : {0, 1, 2, 3, 4}) x.push_back(n);
        CHECK(x.size() == 5);

        CHECK(x[1] == 1);
        CHECK(x[3] == 3);
        
        static_assert(noexcept(x[1]));
    }

    TEST_CASE("HW 6 subscript on const", "[vec-subscript]") {
        Vector<int> x;
        for (auto n : {0, 1, 2, 3, 4}) x.push_back(n);

        const auto y = x;
        CHECK(y.size() == 5);
        CHECK_FALSE(y.data() == nullptr);
        CHECK(y[1] == 1);
        CHECK(y.data()[1] == 1);
        CHECK(y[3] == 3);
        CHECK(y.data()[3] == 3);
    }
}
