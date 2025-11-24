#include <ics_vector.hpp>
#include <ics_vector.hpp>
#include <catch_amalgamated.hpp>

namespace {
    TEST_CASE("HW 6 swap elements length 5 ", "[vec-swap-elements]") {
        Vector<int> x;
        for (auto n : {0, 1, 2, 3, 4}) x.push_back(n);
        
        auto left = x.begin();
        auto right = x.begin() + 4;

        x.swap_elements(left, right);
        x.swap_elements(left+1, right-1);

        CHECK(x[0] == 4);
        CHECK(x[1] == 3);
        CHECK(x[2] == 2);
        CHECK(x[3] == 1);
        CHECK(x[4] == 0);
    }

    TEST_CASE("HW 6 swap elements length 24 ", "[vec-swap-elements]") {
        Vector<int> x;
        for (int i = 0; i < 24; i++) x.push_back(i);
        
        auto left = x.begin();
        auto right = x.begin() + 23;

        for (int i = 0; i < 12; i++) {
            x.swap_elements(left+i, right-i);
        }

        for (int i = 0; i < 24; i++) {
            CHECK(x[i] == 24-i-1);
        }
    }

    TEST_CASE("HW 6 swap elements move only", "[vec-swap-elements]") {
        struct MoveOnly {
            int x;
            MoveOnly() : x{0} {}
            MoveOnly(int x) : x {x} {}
            
            MoveOnly(const MoveOnly&) = delete;
            MoveOnly&operator=(const MoveOnly&) = delete;

            MoveOnly(MoveOnly&&)noexcept = default;
            MoveOnly&operator=(MoveOnly&&) noexcept= default;
            ~MoveOnly() noexcept= default;
            
            bool operator==(int x) const noexcept {
                return this->x == x;
            }
        };

        Vector<MoveOnly> x;
        for (auto n : {0, 1, 2, 3, 4}) x.push_back(n);
        
        auto left = x.begin();
        auto right = x.begin() + 4;

        x.swap_elements(left, right);
        x.swap_elements(left+1, right-1);
        
        static_assert(noexcept(x.swap_elements(left, right)));

        CHECK(x[0] == 4);
        CHECK(x[1] == 3);
        CHECK(x[2] == 2);
        CHECK(x[3] == 1);
        CHECK(x[4] == 0);
    }
}
