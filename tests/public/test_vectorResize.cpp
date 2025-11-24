#include <catch_amalgamated.hpp>
#include <ics_vector.hpp>

struct MoveOnly {
    MoveOnly() = default;

    MoveOnly(const MoveOnly &) = delete;
    MoveOnly & operator=(const MoveOnly &) = delete;

    MoveOnly(MoveOnly &&) noexcept = default;
    MoveOnly & operator=(MoveOnly &&) noexcept = default;

    ~MoveOnly() noexcept = default;
};

static_assert(sizeof(MoveOnly) > 0);

namespace {
    TEST_CASE("HW 6 resize moves", "[resize]") {
        Vector<MoveOnly> x(5);
        x.push_back(MoveOnly{});
        x.push_back(MoveOnly{});
        x.push_back(MoveOnly{});

        auto cap = x.capacity();
        x.resize(10);
        CHECK(x.capacity() != cap);
    }

    TEST_CASE("HW 6 resize removes items", "[resize]") {
        Vector<int> x;
        for (auto n : {0, 1, 2, 3, 4, 5}) x.push_back(n);

        CHECK(x.size() == 6);
        x.resize(4);
        CHECK(x.size() == 4);
        CHECK(x[0] == 0);
        CHECK(x.back() == 3);
    }
} // namespace
