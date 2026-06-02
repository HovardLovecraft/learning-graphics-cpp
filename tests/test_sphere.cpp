#include "doctest.h"
#include "Sphere.h"

const double shadowAcne{0.001};

TEST_CASE("Direct hit in the Sphere surface"){

    const Material mat{Vec3(0.9, 0.9, 0.9), 0.5};
    Sphere sphere{Vec3{0.0, 0.0, -5.0}, mat, 1.0};
    Ray ray{Vec3{0.0, 0.0, 0.0}, Vec3{0.0, 0.0, -1.0}};
    double t = sphere.hit(ray, shadowAcne);
    CHECK(t == doctest::Approx(4.0).epsilon(1e-9));
}

TEST_CASE("Ray misses the Sphere surface, ray passes right from the sphere"){
    const Material mat{Vec3(0.9, 0.9, 0.9), 0.5};
    Sphere sphere{Vec3{0.0, 0.0, -5.0}, mat, 1.0};
    Ray ray{Vec3{0.0, 0.0, 0.0}, Vec3{5.0, 0.0, -1.0}};
    double t = sphere.hit(ray, shadowAcne);
    CHECK(t == doctest::Approx(-1.0).epsilon(1e-9));
}

TEST_CASE("Ray scratches the surface of the sphere"){
    const Material mat{Vec3(0.9, 0.9, 0.9), 0.5};
    Sphere sphere{Vec3{0.0, 0.0, -5.0}, mat, 1.0};
    Ray ray{Vec3{0.0, 1.0, 0.0}, Vec3{0.0, 0.0, -1.0}};
    double t = sphere.hit(ray, shadowAcne);
    CHECK(t == doctest::Approx(5.0).epsilon(1e-9));
}

TEST_CASE("Ray misses the Sphere surface, ray goes opposite way from sphere"){
    const Material mat{Vec3(0.9, 0.9, 0.9), 0.5};
    Sphere sphere{Vec3{0.0, 0.0, -5.0}, mat, 1.0};
    Ray ray{Vec3{0.0, 0.0, 0.0}, Vec3{0.0, 0.0, 6.0}};
    double t = sphere.hit(ray, shadowAcne);
    CHECK(t == doctest::Approx(-1.0).epsilon(1e-9));
}

TEST_CASE("Ray starts moving inside the sphere"){
    const Material mat{Vec3(0.9, 0.9, 0.9), 0.5};
    Sphere sphere{Vec3{0.0, 0.0, -5.0}, mat, 1.0};
    Ray ray{Vec3{0.0, 0.0, -5.0}, Vec3{0.0, 0.0, 6.0}};
    double t = sphere.hit(ray, shadowAcne);
    CHECK(t == doctest::Approx(0.166666667).epsilon(1e-9));
}

TEST_CASE("Ray starts moving almost near the sphere surface"){
    const Material mat{Vec3(0.9, 0.9, 0.9), 0.5};
    Sphere sphere{Vec3{0.0, 0.0, -5.0}, mat, 2.0};
    Ray ray{Vec3{0.0, 0.0, -2.99999}, Vec3{0.0, 0.0, -1.0}};
    double t = sphere.hit(ray, shadowAcne);
    CHECK(t == doctest::Approx(4.00001).epsilon(1e-4));
}

