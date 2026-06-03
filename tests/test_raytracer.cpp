#include "doctest.h"
#include "RayTracer.h"

const double shadowAcne{0.001};
const Material mat{Vec3(0.9, 0.9, 0.9), 0.5};

// Light logic

TEST_CASE("One sphere in front, direct hit"){

    Ray ray{Vec3{0.0, 0.0, 0.0}, Vec3{0.0, 0.0, -1.0}};
    Sphere sphere1{Vec3{0.0, 0.0, -5.0}, mat, 1.0};

    std::vector<Sphere> spheres;
    spheres.reserve(1);
    spheres.push_back(sphere1);

    auto [closestT, closestSphere] = traceRay(ray, spheres, shadowAcne);
    CHECK(closestT == doctest::Approx(4.0).epsilon(1e-9));
    CHECK(closestSphere == &spheres.at(0));
}

TEST_CASE("Two spheres in front, direct hit"){

    Ray ray{Vec3{0.0, 0.0, 0.0}, Vec3{0.0, 0.0, -1.0}};
    Sphere sphere1{Vec3{0.0, 0.0, -5.0}, mat, 1.0};
    Sphere sphere2{Vec3{0.0, 0.0, -9.0}, mat, 1.0};

    std::vector<Sphere> spheres;
    spheres.reserve(2);
    spheres.push_back(sphere1);
    spheres.push_back(sphere2);


    auto [closestT, closestSphere] = traceRay(ray, spheres, shadowAcne);
    CHECK(closestT == doctest::Approx(4.0).epsilon(1e-9));
    CHECK(closestSphere == &spheres.at(0));
}

TEST_CASE("Ray origin inside the sphere"){

    Ray ray{Vec3{0.0, 0.0, -5.0}, Vec3{0.0, 0.0, -6.0}};
    Sphere sphere1{Vec3{0.0, 0.0, -5.0}, mat, 1.0};
    Sphere sphere2{Vec3{1.0, 1.0, -9.0}, mat, 1.0};

    std::vector<Sphere> spheres;
    spheres.reserve(2);
    spheres.push_back(sphere1);
    spheres.push_back(sphere2);

    auto [closestT, closestSphere] = traceRay(ray, spheres, shadowAcne);
    CHECK(closestT == doctest::Approx(0.166666667).epsilon(1e-9));
    CHECK(closestSphere == &spheres.at(0));

}

TEST_CASE("One sphere in front, ray doesn't hit the sphere"){
    
    Sphere sphere{Vec3{0.0, 0.0, -5.0}, mat, 1.0};
    Ray ray{Vec3{0.0, 0.0, 0.0}, Vec3{0.0, 0.0, 1.0}};

    std::vector<Sphere> spheres;
    spheres.reserve(2);
    spheres.push_back(sphere);

    auto [closestT, closestSphere] = traceRay(ray, spheres, shadowAcne);
    CHECK(closestT == doctest::Approx(-1.0).epsilon(1e-9));
    CHECK(closestSphere == nullptr);
}

// Shadow logic

TEST_CASE("The sphere between origin and light is in Shadow"){

    Sphere sphere{Vec3{0.0, 0.0, -5.0}, mat, 1.0};
    Ray shadowRay{Vec3{0.0, 0.0, 0.0}, Vec3{0.0, 0.0, -1.0}};
    Vec3 lightPos{0.0, 0.0, -7.0};

    std::vector<Sphere> spheres;
    spheres.reserve(2);
    spheres.push_back(sphere);

    bool inShadow = isInShadow(shadowRay, lightPos, spheres, shadowAcne);
    CHECK(inShadow == true);
}

TEST_CASE("The sphere is behind the light - no shadow"){

    Sphere sphere{Vec3{0.0, 0.0, -9.0}, mat, 1.0};
    Ray shadowRay{Vec3{0.0, 0.0, 0.0}, Vec3{0.0, 0.0, -1.0}};
    Vec3 lightPos{0.0, 0.0, -7.0};

    std::vector<Sphere> spheres;
    spheres.reserve(2);
    spheres.push_back(sphere);

    bool inShadow = isInShadow(shadowRay, lightPos, spheres, shadowAcne);
    CHECK(inShadow == false);
}

TEST_CASE("The sphere is behind the hit point - no shadow"){

    Sphere sphere{Vec3{0.0, 0.0, 5.0}, mat, 1.0};
    Ray shadowRay{Vec3{0.0, 0.0, 0.0}, Vec3{0.0, 0.0, -1.0}};
    Vec3 lightPos{0.0, 0.0, -7.0};

    std::vector<Sphere> spheres;
    spheres.reserve(2);
    spheres.push_back(sphere);

    bool inShadow = isInShadow(shadowRay, lightPos, spheres, shadowAcne);
    CHECK(inShadow == false);
}