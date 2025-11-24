#include <catch_amalgamated.hpp>
#include <ics_vector.hpp>

namespace {
    TEST_CASE("HW 6 clear elements length 5", "[vec-clear]") {
        Vector<int> x;
        for (auto n : {0, 1, 2, 3, 4}) x.push_back(n);

        CHECK_FALSE(x.empty());

        x.clear();

        CHECK(x.empty());
    }
    
    TEST_CASE("HW 6 clear on empty", "[vec-clear]") {
        Vector<int> x(5);

        auto * data = x.data();
        CHECK(x.empty());
        static_assert(noexcept(x.clear()));
        
        x.clear();
        
        CHECK(x.empty());
        CHECK(x.data() == data);
    }

    TEST_CASE("HW 6 clear does not change capacity", "[vec-clear]") {
        Vector<int> x;
        for (auto n : {0, 1, 2, 3, 4}) x.push_back(n);

        CHECK_FALSE(x.empty());

        auto old_cap = x.capacity();

        x.clear();

        CHECK(x.empty());
        CHECK(x.capacity() == old_cap);
    }

    TEST_CASE("HW 6 clear deletes each item", "[vec-clear]") {
        int count = 0;

        struct NoisyDelete {
            int * count{nullptr};

            explicit NoisyDelete(int * counter = nullptr)
                : count{counter} {}

            NoisyDelete(const NoisyDelete &) = default;
            NoisyDelete & operator=(const NoisyDelete &) = default;

            NoisyDelete(NoisyDelete && other)
                : count{other.count} {
                other.count = nullptr;
            }

            NoisyDelete & operator=(NoisyDelete && other) {
                count = other.count;
                other.count = nullptr;
                return *this;
            }

            ~NoisyDelete() noexcept {
                if (count != nullptr) ++(*count);
            }
        };

        static constexpr auto test_size = 3;

        Vector<NoisyDelete> x(test_size * 2);
        for (auto n = 0; n < test_size; ++n) x.push_back(NoisyDelete{&count});

        CHECK_FALSE(x.empty());

        x.clear();

        CHECK(x.empty());
        CHECK(count == test_size);
    }
} // namespace
