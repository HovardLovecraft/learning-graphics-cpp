#include "doctest.h"
#include "Triangle.h"

TEST_CASE("Validate normal formed from triangle is correct"){
    Vec3 B{-0.5, -0.5, 0.5};
    Vec3 C{0.5, -0.5, 0.5};
    Vec3 E{-0.5, 0.5, 0.5};
    Triangle t{B, C, E};

    CHECK(t.normal.x == doctest::Approx(0.0).epsilon(1e-9));
    CHECK(t.normal.y == doctest::Approx(0.0).epsilon(1e-9));
    CHECK(t.normal.z == doctest::Approx(1.0).epsilon(1e-9));
}