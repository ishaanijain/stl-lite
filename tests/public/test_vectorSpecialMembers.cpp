#include <type_traits>

#include <catch_amalgamated.hpp>
#include <ics_vector.hpp>
#include <ics_vector.hpp>

namespace {
    TEST_CASE("Vector is movable", "[vector-special-members]") {
        CHECK(std::is_nothrow_move_assignable_v<Vector<int>>);
        CHECK(std::is_nothrow_move_constructible_v<Vector<int>>);
    }

    TEST_CASE("Vector is copyable", "[vector-special-members]") {
        CHECK(std::is_copy_assignable_v<Vector<int>>);
        CHECK(std::is_copy_constructible_v<Vector<int>>);
    }

    TEST_CASE("Vector is destructable", "[vector-special-members]") {
        CHECK(std::is_nothrow_destructible_v<Vector<int>>);
    }

    TEST_CASE("Vector has a default constructor for empty", "[vector-special-members]") {
        CHECK(std::is_default_constructible_v<Vector<int>>);

        Vector<int> vec;

        CHECK(vec.size() == 0);
        CHECK(vec.capacity() == 0);
        CHECK(vec.data() == nullptr);
        CHECK(vec.empty());
        
        static_assert(noexcept(vec.data()));
        static_assert(noexcept(vec.capacity()));
        static_assert(noexcept(vec.size()));
        static_assert(noexcept(vec.empty()));
    }

    TEST_CASE("Vector has a constructor for initial capacity", "[vector-special-members]") {
        CHECK(std::is_constructible_v<Vector<int>, size_t>);

        Vector<int> vec(5);

        CHECK(vec.size() == 0);
        CHECK(vec.empty());

        CHECK(vec.capacity() == 5);
        CHECK_FALSE(vec.data() == nullptr);
    }

    TEST_CASE("Copy assignment clears the destination", "[vector-special-members]") {
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
        Vector<NoisyDelete> y(test_size * 2);
        for (auto n = 0; n < test_size; ++n) {
            x.push_back(NoisyDelete{&count});
            y.push_back(NoisyDelete{&count});
        }

        CHECK_FALSE(x.empty());
        CHECK_FALSE(y.empty());

        y = x;

        CHECK(count == test_size);
    }

    TEST_CASE("Move assignment clears the old destination and empties the source", "[vector-special-members]") {
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
        Vector<NoisyDelete> y(test_size * 2);
        for (auto n = 0; n < test_size; ++n) {
            x.push_back(NoisyDelete{&count});
            y.push_back(NoisyDelete{&count});
        }

        CHECK_FALSE(x.empty());
        CHECK_FALSE(y.empty());

        y = std::move(x);

        CHECK(count == test_size);
        CHECK(x.empty());
    }

    TEST_CASE("Move constructor empties the source", "[vector-special-members]") {
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
        for (auto n = 0; n < test_size; ++n) {
            x.push_back(NoisyDelete{&count});
        }

        CHECK_FALSE(x.empty());

        const Vector y{std::move(x)};

        CHECK(count == 0);
        CHECK(x.empty());
        CHECK(y.size() == test_size);
    }
} // namespace
