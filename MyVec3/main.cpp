//
//  main.cpp
//  MyVec3
//
//  Created by Ivan Kuznetsov on 25.05.2026.
//

#include <iostream>
#include <fstream>
#include <random>
#include <utility>
#include <vector>
#include "Mat4.h"
#include "Vec3.h"
#include "Ray.h"
#include "RayTracer.h"
#include "Sphere.h"
#include "Camera.h"
#include "Color.h"
#include "Renderer.h"
#include "Scene.h"

int main(int argc, const char * argv[]) {
    
    // Scene configuration
    const int imageWidth{800};
    const int imageHeight{600};
    const int samplesPerPixel = 16;
    const int maxBounces = 3;
    const double ambient = 0.25;
    const double shadowAcne = 0.001;
    const Vec3 lightPos{-4.0, 2.0, 2.0};

    //Camera
    Vec3 eye = Vec3{0,0,0};
    Vec3 target = Vec3{0,0,-1};
    Vec3 upDir = Vec3{0,1,0};
    double fov{90.0};
    double aspect{double(imageWidth) / imageHeight};
    double near{0.1};
    double far{100.0};
    Camera cam{eye, target, upDir, fov, aspect, near, far};

    //Objects 
    const Material gloss{Vec3(1.0, 0.0, 0.0), 0.8};
    const Material mat{Vec3(0.7, 0.7, 0.7), 0.5};
    const Material blacky{Vec3(0.1, 0.1, 0.1), 0.05};
    const Sphere sphere{Vec3{0.0, 0.0, -7.0}, gloss, 0.5};
    const Sphere sphere2{Vec3{-0.8, 0.4, -5.5}, mat, 0.3};
    const Sphere sphere3{Vec3{-1.4, 0.7, -4.0}, blacky, 0.1};
    std::vector<Sphere> spheres;

    spheres.reserve(5);
    spheres.push_back(sphere);
    spheres.push_back(sphere2);
    spheres.push_back(sphere3);
    
    const Scene scene{imageWidth, imageHeight, samplesPerPixel, maxBounces, ambient, shadowAcne, lightPos, cam, spheres};
    render(scene, "output/image.ppm");
    
    return EXIT_SUCCESS;
}
