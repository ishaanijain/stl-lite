#include "ics_vector.hpp"
#include "ics_vector.hpp"

#include <catch_amalgamated.hpp>

// Test correct behavior (no-throwing)
namespace {
    // Capacity tests.
    TEST_CASE("HW 6 Vector Pop on 2 elements", "[vector-popback]") {
        Vector<int> vec;
        vec.push_back(5);
        vec.push_back(4);

        CHECK(vec.back() == 4);
        CHECK(vec.size() == 2);
        vec.pop_back();
        CHECK(vec.back() == 5);
        vec.pop_back();
        CHECK(vec.size() == 0);

        CHECK(vec.begin() == vec.end());
    }

    TEST_CASE("HW 6 Vector Pop on 1 element", "[vector-popback]") {
        // Capacity doubling test.
        Vector<int> vec;
        vec.push_back(5);
        CHECK(vec.back() == 5);

        vec.pop_back();
        CHECK(vec.size() == 0);

        CHECK(vec.begin() == vec.end());
    }

    TEST_CASE("HW 6 Vector Pop destroys item", "[vector-popback]") {
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

        Vector<NoisyDelete> vec;
        vec.push_back(NoisyDelete{&count});
        vec.pop_back();

        CHECK(vec.empty());
        CHECK(count == 1);
    }

    TEST_CASE("HW 6 Vector Pop on Empty", "[vector-popback]") {
        Vector<int> v;
        CHECK_THROWS_MATCHES(
            v.pop_back(),
            VectorException, 
            Catch::Matchers::Message("popping from empty on vector")
        );
    }
} // namespace
