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
#include "Vec3.h"
#include "Ray.h"
#include "RayTracer.h"
#include "Sphere.h"
#include "Camera.h"
#include "Color.h"

int main(int argc, const char * argv[]) {
    
    const int imageWidth{800};
    const int imageHeight{600};
    const int samplesPerPixel = 16;
    const int maxBounces = 3;
    const double ambient = 0.25;
    const double shadowAcne = 0.001;
    const Material gloss{Vec3(1.0, 0.0, 0.0), 0.8};
    const Material mat{Vec3(0.7, 0.7, 0.7), 0.5};
    const Material blacky{Vec3(0.1, 0.1, 0.1), 0.05};
    const Camera cam{Vec3{0.0, 0.0, 1.5}, 3.0, 3.0, 3.0};
    const Sphere sphere{Vec3{0.0, 0.0, -7.0}, gloss, 0.5};
    const Sphere sphere2{Vec3{-0.8, 0.4, -5.5}, mat, 0.3};
    const Sphere sphere3{Vec3{-1.4, 0.7, -4.0}, blacky, 0.1};
    std::vector<Sphere> spheres;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distrib(0, 1.0);
    spheres.reserve(5);
    spheres.push_back(sphere);
    spheres.push_back(sphere2);
    spheres.push_back(sphere3);
    const Vec3 lightPos{-4.0, 2.0, 2.0};
    
    std::ofstream file("output/image.ppm");
    if (!file) {
        std::cerr << "Failed to open file!\n";
        return 1;
    }
    
    file << "P3\n";
    file << imageWidth << " " << imageHeight << "\n";
    file << "255\n";
    
    for (int row{0}; row < imageHeight; ++row) {
        for (int col {0}; col < imageWidth; ++col) {
            
            Vec3 totalColor{0, 0, 0};
            
            for (int s = 0; s < samplesPerPixel; ++s) { // anti alliasing for sphere to look more smooth
                double u = double((col + distrib(gen)) / (imageWidth - 1.0));
                double v = double((row + distrib(gen)) / (imageHeight-1.0));
                double colorMultiplier = 1.0;
                Ray ray = cam.getRay(u, v);
                Ray currentRay = ray;
                
                
                for (int bounce = 0; bounce < maxBounces; ++bounce){
                    
                    auto [closestT, closestSphere] = traceRay(currentRay, spheres);
                    
                    if (closestT < 0) {
                        break;
                    }
                    
                    if (closestT > 0) {
                        Vec3 P = currentRay.origin + currentRay.direction * closestT; // point of hit
                        Vec3 N = (P - closestSphere->center).normalize(); // normal
                        currentRay = Ray{P + N * shadowAcne, currentRay.direction.reflect(N)};
                        Vec3 lightDir = (lightPos - P).normalize(); // direction of light it goes from point of hit to lightPos
                        Ray shadowRay = Ray{P + N * shadowAcne, lightDir};
                        
                        bool inShadow = false;
                        for (const Sphere& s : spheres) {
                            double t = s.hit(shadowRay);
                            if (t > 0) {
                                inShadow = true;
                                break;
                            }
                        }
                        
                        // brightness
                        double brightness;
                        if (inShadow) {
                            brightness = ambient;
                        } else {
                            brightness = std::min(1.0, ambient + std::max(0.0, N.dot(lightDir))); // brightness is defined by cos of angle between normal and lightdir
                        }
                        
                        Vec3 diffuse = closestSphere->material.albedo * brightness;
                        totalColor = totalColor + diffuse * colorMultiplier;
                        colorMultiplier *= closestSphere->material.reflectionRate;
                    }
                }
            }
            Vec3 finalColor = totalColor / samplesPerPixel;
            int r = int(finalColor.x * 255);
            int g = int(finalColor.y * 255);
            int b = int(finalColor.z * 255);
            file << r << " " << g << " " << b << "\n";
        }
    }
    
    file.close();
    std::cout << "We are done !\n";
    
    return EXIT_SUCCESS;
}
