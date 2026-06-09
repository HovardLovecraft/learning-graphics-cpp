#include "doctest.h"
#include "Framebuffer.h"

const int imageWidth{1};
const int imageHeight{1};

TEST_CASE("new depth smaller → check that pixel is updated:"){
    Framebuffer fb(imageWidth, imageHeight);
    fb.setPixel(0, 0, Vec3{1, 1, 1}, 0.5);
    fb.setPixel(0, 0, Vec3{0.5, 0.5, 0.5}, 0.3);
    CHECK(fb.pixels[0].x == doctest::Approx(0.5).epsilon(1e-9));
    CHECK(fb.pixels[0].y == doctest::Approx(0.5).epsilon(1e-9));
    CHECK(fb.pixels[0].z == doctest::Approx(0.5).epsilon(1e-9));
}

TEST_CASE("new depth bigger → check that pixel is NOT updated:"){
    Framebuffer fb(imageWidth, imageHeight);
    fb.setPixel(0, 0, Vec3{1, 1, 1}, 0.5);
    fb.setPixel(0, 0, Vec3{0.5, 0.5, 0.5}, 0.7);
    CHECK(fb.pixels[0].x == doctest::Approx(1.0).epsilon(1e-9));
    CHECK(fb.pixels[0].y == doctest::Approx(1.0).epsilon(1e-9));
    CHECK(fb.pixels[0].z == doctest::Approx(1.0).epsilon(1e-9));
}