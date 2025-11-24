#include "ics_vector.hpp"
#include "ics_vector.hpp"
#include "vector_exception.hpp"

#include <type_traits>

#include <catch_amalgamated.hpp>

namespace {
    TEST_CASE("HW 6 Vec Iterator has no handwritten destructor") {
        Vector<int> vec;
        CHECK(std::is_trivially_destructible_v<decltype(vec.begin())>);
    }

    TEST_CASE("HW 6 Vec Iterator is movable") {
        Vector<int> vec;
        auto iter = vec.begin();

        CHECK(std::is_nothrow_move_assignable_v<decltype(iter)>);
        CHECK(std::is_nothrow_move_constructible_v<decltype(iter)>);
    }

    TEST_CASE("HW 6 Vec Iterator is copyable") {
        Vector<int> vec;
        auto iter = vec.begin();

        CHECK(std::is_nothrow_copy_assignable_v<decltype(iter)>);
        CHECK(std::is_nothrow_copy_constructible_v<decltype(iter)>);
    }

    TEST_CASE("HW 6 Vec Iterator can walk forward", "[iterator]") {
        Vector<int> vec;
        vec.push_back(0);
        vec.push_back(1);
        vec.push_back(2);

        auto iter = vec.begin();

        CHECK(*iter == 0);
        ++iter;
        CHECK(*iter == 1);
    }

    TEST_CASE("HW 6 Vec Iterator copy", "[iterator]") {
        Vector<int> vec;
        vec.push_back(0);
        vec.push_back(1);
        vec.push_back(2);

        auto iter = vec.begin();
        auto copy = iter;
        CHECK(copy == iter);

        ++iter;
        CHECK(*copy == 0);
        CHECK(*iter == 1);
        CHECK(copy != iter);
    }

    TEST_CASE("HW 6 Vec Iterator preinc is like postinc") {
        Vector<int> vec;
        vec.push_back(0);
        vec.push_back(1);
        vec.push_back(2);

        auto iter = vec.begin();
        auto copy = iter;

        iter++;
        ++copy;

        CHECK(iter == copy);
    }

    TEST_CASE("HW 6 Vec Iterator can walk backwards", "[iterator]") {
        Vector<int> vec;
        vec.push_back(0);
        vec.push_back(1);
        vec.push_back(2);

        auto iter = vec.end();
        --iter;

        CHECK(*iter == 2);
        iter--;
        CHECK(*iter == 1);
    }

    TEST_CASE("HW 6 Vec Iterator can be added to", "[iterator]") {
        Vector<int> vec;
        vec.push_back(0);
        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);
        vec.push_back(4);

        auto iter = vec.begin();
        auto copy = iter;

        iter = iter + 2;
        CHECK(iter != copy);
        CHECK(*iter == 2);

        copy = 2 + copy;
        CHECK(iter == copy);
    }
    
    TEST_CASE("HW 6 iterators support += and -=", "[iterator]"){
        Vector<int> vec;
        vec.push_back(0);
        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);
        vec.push_back(4);

        auto iter = vec.begin();
        auto copy = iter;

        iter += 2;
        CHECK(iter != copy);
        CHECK(*iter == 2);

        iter -= 2;
        CHECK(iter == copy);

    }

    TEST_CASE("HW 6 const Vec iterators are pointers", "[iterator]"){
        const Vector<int> vec;
        using const_begin_iter_t = decltype(vec.begin());
        using const_end_iter_t = decltype(vec.end());
        CHECK(std::is_same_v<const_begin_iter_t, const_end_iter_t>);
        CHECK(std::is_pointer_v<const_begin_iter_t>);
        CHECK(std::is_same_v<const_begin_iter_t, const int *>);
    }
    
    TEST_CASE("HW 6 iterators have -> overloaded", "[iterator]"){
        Vector<std::string> x;
        for(auto s : {"", "h", "he", "hel", "hell", "hello"}) x.push_back(s);
        
        for(auto iter = x.begin(); iter != x.end(); ++iter) {
            CHECK(iter->size() == iter - x.begin());
        }
    }
} // namespace
