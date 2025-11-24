#include "ics_vector.hpp"
#include "vector_exception.hpp"

#include <catch_amalgamated.hpp>

namespace {
    TEST_CASE("HW 6 Vec Exception Test", "[vecexception]") {
        auto v = VectorException("test exception");
        CHECK(v.what() == std::string{"test exception on vector"});
    }
} // namespace
