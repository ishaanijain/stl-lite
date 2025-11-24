#include <ics_vector.hpp>
#include <catch_amalgamated.hpp>
#include <sstream>

namespace {
    TEST_CASE("HW 6 print const", "[print]") {
        Vector<int> x;
        for(auto val : {1,2,3,4,5}) x.push_back(val);
        
        const Vector y = x;
        
        std::stringstream ss;
        ss << y;

        CHECK(ss.str() == "1 2 3 4 5 ");
    }

    TEST_CASE("HW 6 print mutating", "[print]") {
        std::stringstream ss;
        ss << Vector<int>{};

        CHECK(ss.str() == "");
    }

    TEST_CASE("HW 6 print string", "[print]") {
        Vector<std::string> x;
        for(auto val : {"hello", "world"}) x.push_back(val);
        
        const Vector y = x;
        
        std::stringstream ss;
        ss << y;

        CHECK(ss.str() == "hello world ");
    }
}