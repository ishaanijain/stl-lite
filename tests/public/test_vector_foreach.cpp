#include <ics_vector.hpp>
#include <ics_vector.hpp>
#include <catch_amalgamated.hpp>

namespace {
    TEST_CASE("HW 6 For each const", "[foreach]") {
        Vector<int> x;
        for(auto val : {1,2,3,4,5}) x.push_back(val);
        const auto y = x;
        
        auto expected = 1;
        for(auto val : y){
            CHECK(val == expected);
            ++expected;
        }
    }

    TEST_CASE("HW 6 For each mutating", "[foreach]") {
        Vector<int> x;
        for (auto val : {1,2,3,4,5}) x.push_back(val);
        
        for(auto & val : x){
            --val;
        }

        auto expected = 0;
        for(auto val : x) {
            CHECK(val == expected);
            ++expected;
        }
    }
}