#include <ics_vector.hpp>
#include <ics_vector.hpp>
#include <catch_amalgamated.hpp>

namespace {
    TEST_CASE("HW 6 at access", "[at]") {
        Vector<int> x;
        for (auto val : {0,1,2,3,4,5}) x.push_back(val);
        
        static_assert(not noexcept(x.at(2)));
        
        CHECK(x.at(2) == 2);
    }

    TEST_CASE("HW 6 const at access", "[at]") {
        Vector<int> x;
        for (auto val : {0,1,2,3,4,5}) x.push_back(val);
        
        const auto y = x;
        
        CHECK(y.at(2) == 2);
    }

    TEST_CASE("HW 6 out of bounds at access index 0 on empty", "[at]") {
        Vector<int> x;

        CHECK_THROWS_MATCHES(
            x.at(0),
            VectorException, 
            Catch::Matchers::Message("out of bounds on vector")
        );
    }

    TEST_CASE("HW 6 out of bounds at access index 1 on size 1", "[at]") {
        Vector<int> x;
        x.push_back(0);

        CHECK_THROWS_MATCHES(
            x.at(1),
            VectorException, 
            Catch::Matchers::Message("out of bounds on vector")
        );
    }
}