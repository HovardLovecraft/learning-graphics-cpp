#include "doctest.h"
#include "Sphere.h"


TEST_CASE("Direct hit in the Sphere surface"){
    Sphere sphere{Vec3{0.0, 0.0, -5.0}, 1.0};
    Ray ray{Vec3{0.0, 0.0, 0.0}, Vec3{0.0, 0.0, -1.0}};
    double t = sphere.hit(ray);
    CHECK(t == doctest::Approx(4.0).epsilon(1e-9));
}

TEST_CASE("Ray misses the Sphere surface, ray passes right from the sphere"){
    Sphere sphere{Vec3{0.0, 0.0, -5.0}, 1.0};
    Ray ray{Vec3{0.0, 0.0, 0.0}, Vec3{5.0, 0.0, -1.0}};
    double t = sphere.hit(ray);
    CHECK(t == doctest::Approx(-1.0).epsilon(1e-9));
}

TEST_CASE("Ray scratches the surface of the sphere"){
    Sphere sphere{Vec3{0.0, 0.0, -5.0}, 1.0};
    Ray ray{Vec3{0.0, 1.0, 0.0}, Vec3{0.0, 0.0, -1.0}};
    double t = sphere.hit(ray);
    CHECK(t == doctest::Approx(5.0).epsilon(1e-9));
}

TEST_CASE("Ray misses the Sphere surface, ray goes opposite way from sphere"){
    Sphere sphere{Vec3{0.0, 0.0, -5.0}, 1.0};
    Ray ray{Vec3{0.0, 0.0, 0.0}, Vec3{0.0, 0.0, 6.0}};
    double t = sphere.hit(ray);
    CHECK(t == doctest::Approx(-1.0).epsilon(1e-9));
}

