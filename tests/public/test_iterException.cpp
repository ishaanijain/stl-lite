#include "ics_vector.hpp"
#include "vector_exception.hpp"

#include <catch_amalgamated.hpp>

namespace {
    TEST_CASE("HW 6 iter Exception prev post dec on empty", "[vecexception]") {
        Vector<int> v;

        auto iter = v.begin();
        
        CHECK_THROWS_MATCHES(
            iter--,
            VectorException, 
            Catch::Matchers::Message("out of bounds on vector")
        );
    }

    TEST_CASE("HW 6 iter Exception prev pre dec on empty", "[vecexception]") {
        Vector<int> v;

        auto iter = v.begin();

        CHECK_THROWS_MATCHES(
            --iter,
            VectorException, 
            Catch::Matchers::Message("out of bounds on vector")
        );
    }

    TEST_CASE("HW 6 Vec Iterator preinc throws on out of bounds", "[vecexception]") {
        Vector<int> vec;
        vec.push_back(0);
        vec.push_back(1);
        vec.push_back(2);

        auto iter = vec.begin();

        try {
            ++iter;
            ++iter;
            ++iter;
            ++iter;
        } catch (VectorException & e) {
            CHECK(std::string{"out of bounds on vector"} == e.what());
            return;
        }
        CHECK(false);
    }

    TEST_CASE("Iterators from different vectors cannot be subtracted") {
        Vector<int> vecX;
        Vector<int> vecY;

        CHECK_THROWS_MATCHES(
            vecY.begin() - vecX.begin(), VectorException,
            Catch::Matchers::Message("iterators point to different containers on vector"));
    }

    TEST_CASE("HW 6 Vec Iterator += throws on out of bounds", "[vecexception]") {
        Vector<int> vec;
        vec.push_back(0);
        vec.push_back(1);
        vec.push_back(2);

        auto iter = vec.begin();

        CHECK_THROWS_MATCHES(
            iter += 5,
            VectorException, 
            Catch::Matchers::Message("out of bounds on vector")
        );
    }

    TEST_CASE("HW 6 Vec Iterator -= throws on out of bounds", "[vecexception]") {
        Vector<int> vec;
        vec.push_back(0);
        vec.push_back(1);
        vec.push_back(2);

        auto iter = vec.begin();

        CHECK_THROWS_MATCHES(
            iter -= 5,
            VectorException, 
            Catch::Matchers::Message("out of bounds on vector")
        );
    }

    TEST_CASE("HW 6 Vec Iterator - throws on out of bounds", "[vecexception]") {
        Vector<int> vec;
        vec.push_back(0);
        vec.push_back(1);
        vec.push_back(2);

        auto iter = vec.end();

        CHECK_THROWS_MATCHES(
            iter - 5,
            VectorException, 
            Catch::Matchers::Message("out of bounds on vector")
        );
    }

    TEST_CASE("HW 6 Vec Iterator + throws on out of bounds", "[vecexception]") {
        Vector<int> vec;
        vec.push_back(0);
        vec.push_back(1);
        vec.push_back(2);

        auto iter = vec.begin();

        CHECK_THROWS_MATCHES(
            iter + 5,
            VectorException, 
            Catch::Matchers::Message("out of bounds on vector")
        );
    }

    TEST_CASE("HW 6 Vec Iterator * throws on out of bounds", "[vecexception]") {
        Vector<int> vec;
        vec.push_back(0);
        vec.push_back(1);
        vec.push_back(2);

        auto iter = vec.end();

        CHECK_THROWS_MATCHES(
            *iter,
            VectorException, 
            Catch::Matchers::Message("out of bounds on vector")
        );
    }
} // namespace
