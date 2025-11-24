#include <ics_vector.hpp>
#include <catch_amalgamated.hpp>

namespace {
    TEST_CASE("HW 6 erase at end", "[erase]") {
        Vector<int> x;
        for (auto val : {1,2,3,4,5}) x.push_back(val);
        
        auto iter = x.begin();
        ++iter;
        ++iter;
        ++iter;
        CHECK(*iter == 4);
        x.erase(iter, x.end());
        CHECK(x.size() == 3);
        
        static_assert(not noexcept(x.erase(iter, x.end())));
    }

    TEST_CASE("HW 6 erase at beginning", "[erase]") {
        Vector<int> x;
        for (auto val : {0,1,2,3,4,5}) x.push_back(val);
        
        auto iter = x.begin();
        CHECK(*iter == 0);
        x.erase(iter, iter + 3);
        CHECK(x.front() == 3);
        CHECK(x.size() == 3);
    }

    TEST_CASE("HW 6 erase nothing", "[erase]") {
        Vector<int> x;
        for (auto val : {0,1,2,3,4,5}) x.push_back(val);
        
        auto old_size = x.size();
        auto iter = x.begin();
        CHECK(*iter == 0);
        x.erase(iter, iter);
        CHECK(x.front() == 0);
        CHECK(x.size() == old_size);
    }
}
