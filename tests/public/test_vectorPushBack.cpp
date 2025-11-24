#include <ics_vector.hpp>
#include <catch_amalgamated.hpp>

namespace {
    TEST_CASE("HW 6 push back 5 elements in sequence", "[vec-push-back]") {
        Vector<int> x;
        for (auto n : {0, 1, 2, 3, 4}) x.push_back(n);
        
        CHECK(x[0] == 0);
        CHECK(x[1] == 1);
        CHECK(x[2] == 2);
        CHECK(x[3] == 3);
        CHECK(x[4] == 4);
    }

    TEST_CASE("HW 6 push_back is lazy to reallocate", "[vec-push-back]"){
        Vector<int> vec(6);
        vec.push_back(0);
        auto * data = vec.data();
        CHECK(data != nullptr);
        vec.push_back(1);
        vec.push_back(2);
        CHECK(vec.data() == data);
    }
}
