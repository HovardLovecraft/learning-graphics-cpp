#include "doctest.h"
#include "Vec3.h"

TEST_CASE("Vec3 dot product perpendicular vectors") {
    Vec3 a{1.0, 0.0, 0.0};
    Vec3 b{0.0, 1.0, 0.0};
    CHECK(a.dot(b) == 0.0);  
}

TEST_CASE("Vec3 dot product collinear vectors") {
    Vec3 a{1.0, 0.0, 0.0};
    Vec3 b{2.0, 0.0, 0.0};
    CHECK(a.dot(b) == 2.0);  
}

TEST_CASE("Vec3 dot product opposite directed vectors") {
    Vec3 a{2.0, 0.0, 0.0};
    Vec3 b{-2.0, 0.0, 0.0};
    CHECK(a.dot(b) == -4.0);  
}

TEST_CASE("Vec3 dot product random vectors") {
    Vec3 a{1.0, 1.0, 2.0};
    Vec3 b{2.0, -1.0, 3.0};
    CHECK(a.dot(b) == 7.0);  
}

TEST_CASE("Vec3 cross product X cross Y equals Z axis") {
    Vec3 a{1.0, 0.0, 0.0};
    Vec3 b{0.0, 1.0, 0.0};
    CHECK(a.cross(b).x == 0.0);
    CHECK(a.cross(b).y == 0.0);  
    CHECK(a.cross(b).z == 1.0);    
}

TEST_CASE("Vec3 cross product order matters Y cross X equals negative Z") {
    Vec3 a{0.0, 1.0, 0.0};
    Vec3 b{1.0, 0.0, 0.0};
    CHECK(a.cross(b).x == 0.0);
    CHECK(a.cross(b).y == 0.0);  
    CHECK(a.cross(b).z == -1.0);    
}

TEST_CASE("Vec3 length 3-4-5 triangle") {
    Vec3 a{3.0, 4.0, 0.0};
    CHECK(a.length() == 5.0);
}

TEST_CASE("Vec3 normalize") {
    Vec3 a{3.0, 4.0, 0.0};
    Vec3 result = a.normalize();
    CHECK(result.x == doctest::Approx(0.6).epsilon(1e-9));
    CHECK(result.y == doctest::Approx(0.8).epsilon(1e-9));
    CHECK(result.z == doctest::Approx(0.0).epsilon(1e-9));
}
