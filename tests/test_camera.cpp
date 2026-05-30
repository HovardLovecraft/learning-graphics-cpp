#include "doctest.h"
#include "Camera.h"

TEST_CASE("Ray moves directly from camera origin towards the scene through viewport"){
    Camera cam{Vec3{0.0, 0.0, 0.0}, 3.0, 3.0, 3.0};
    Ray ray = cam.getRay(0.5, 0.5);
    CHECK(ray.origin.x == 0.0);
    CHECK(ray.origin.y == 0.0);
    CHECK(ray.origin.z == 0.0);
    CHECK(ray.direction.x == 0.0);
    CHECK(ray.direction.y == 0.0);
    CHECK(ray.direction.z == -3.0);
}

TEST_CASE("Ray moves to the angle of viewport"){
    Camera cam{Vec3{0.0, 0.0, 0.0}, 3.0, 3.0, 3.0};
    Ray ray = cam.getRay(0.0, 0.0);
    CHECK(ray.origin.x == 0.0);
    CHECK(ray.origin.y == 0.0);
    CHECK(ray.origin.z == 0.0);
    CHECK(ray.direction.x == -1.5);
    CHECK(ray.direction.y == -1.5);
    CHECK(ray.direction.z == -3.0);
}