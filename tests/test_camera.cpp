#include "doctest.h"
#include "Camera.h"

TEST_CASE("Ray moves directly from camera origin towards the scene through viewport"){
    
    Vec3 eye = Vec3{0,0,0};
    Vec3 target = Vec3{0,0,-1};
    Vec3 upDir = Vec3{0,1,0};
    double fov{90.0};
    double aspect{1.0};
    double near{0.1};
    double far{100.0};
    
    Camera cam{eye, target, upDir, fov, aspect, near, far};
    Ray ray = cam.getRay(0.5, 0.5);
    CHECK(ray.origin.x == doctest::Approx(0.0).epsilon(1e-9));
    CHECK(ray.origin.y == doctest::Approx(0.0).epsilon(1e-9));
    CHECK(ray.origin.z == doctest::Approx(0.0).epsilon(1e-9));
    CHECK(ray.direction.x == doctest::Approx(0.0).epsilon(1e-9));
    CHECK(ray.direction.y == doctest::Approx(0.0).epsilon(1e-9));
    CHECK(ray.direction.z == doctest::Approx(-1.0).epsilon(1e-9));
    
    //check camera correct initialization
    CHECK(cam.forward.x == doctest::Approx(0.0).epsilon(1e-9));
    CHECK(cam.forward.y == doctest::Approx(0.0).epsilon(1e-9));
    CHECK(cam.forward.z == doctest::Approx(-1.0).epsilon(1e-9));
    CHECK(cam.right.x == doctest::Approx(1.0).epsilon(1e-9));
    CHECK(cam.right.y == doctest::Approx(0.0).epsilon(1e-9));
    CHECK(cam.right.z == doctest::Approx(0.0).epsilon(1e-9));
    CHECK(cam.up.x == doctest::Approx(0.0).epsilon(1e-9));
    CHECK(cam.up.y == doctest::Approx(1.0).epsilon(1e-9));
    CHECK(cam.up.z == doctest::Approx(0.0).epsilon(1e-9));
}

TEST_CASE("Ray moves to the angle of viewport"){
    Vec3 eye = Vec3{0,0,0};
    Vec3 target = Vec3{0,0,-1};
    Vec3 upDir = Vec3{0,1,0};
    double fov{90.0};
    double aspect{1.0};
    double near{0.1};
    double far{100.0};
    
    Camera cam{eye, target, upDir, fov, aspect, near, far};
    Ray ray = cam.getRay(0.0, 0.0);
    CHECK(ray.origin.x == doctest::Approx(0.0).epsilon(1e-9));
    CHECK(ray.origin.y == doctest::Approx(0.0).epsilon(1e-9));
    CHECK(ray.origin.z == doctest::Approx(0.0).epsilon(1e-9));
    CHECK(ray.direction.x == doctest::Approx(-0.5).epsilon(1e-9));
    CHECK(ray.direction.y == doctest::Approx(-0.5).epsilon(1e-9));
    CHECK(ray.direction.z == doctest::Approx(-1.0).epsilon(1e-9));
}