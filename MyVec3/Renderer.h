//
//  Renderer.h
//  MyVec3
//
//  Created by Ivan Kuznetsov on 04.06.2026.
//

#ifndef Renderer_h
#define Renderer_h

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

#include "Scene.h"


void render(const Scene& scene, const std::string& outputPath){
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distrib(0, 1.0);
    std::ofstream file(outputPath);
    if (!file) {
        std::cerr << "Failed to open file!\n";
        return;
    }

    file << "P3\n";
    file << scene.imageWidth << " " << scene.imageHeight << "\n";
    file << "255\n";
    
    for (int row{0}; row < scene.imageHeight; ++row) {
        for (int col {0}; col < scene.imageWidth; ++col) {
            
            Vec3 totalColor{0, 0, 0};
            
            for (int s = 0; s < scene.samplesPerPixel; ++s) {
                // anti alliasing for sphere to look more smooth
                
                double u = double((col + distrib(gen)) / (scene.imageWidth - 1.0));
                double v = double((row + distrib(gen)) / (scene.imageHeight-1.0));
                double colorMultiplier = 1.0;
                Ray ray = scene.camera.getRay(u, v);
                Ray currentRay = ray;
                
                
                for (int bounce = 0; bounce < scene.maxBounces; ++bounce){
                    //Multi-bounce reflections
                    
                    auto [closestT, closestSphere] = traceRay(currentRay, scene.spheres, scene.shadowAcne);
                    
                    if (closestT < 0) {
                        break;
                    }
                    
                    if (closestT > 0) {
                        Vec3 P = currentRay.origin + currentRay.direction * closestT; // point of hit
                        Vec3 N = (P - closestSphere->center).normalize(); // normal
                        currentRay = Ray{P + N * scene.shadowAcne, currentRay.direction.reflect(N)};
                        Vec3 lightDir = (scene.lightPosition - P).normalize(); // direction of light it goes from point of hit to lightPos
                        Ray shadowRay = Ray{P + N * scene.shadowAcne, lightDir};
                        
                        bool inShadow = isInShadow(shadowRay, scene.lightPosition, scene.spheres, scene.shadowAcne);
                        
                        // brightness
                        double brightness;
                        if (inShadow) {
                            brightness = scene.ambient;
                        } else {
                            brightness = std::min(1.0, scene.ambient + std::max(0.0, N.dot(lightDir))); // brightness is defined by cos of angle between normal and lightdir
                        }
                        
                        Vec3 diffuse = closestSphere->material.albedo * brightness;
                        totalColor = totalColor + diffuse * colorMultiplier;
                        colorMultiplier *= closestSphere->material.reflectionRate;
                    }
                }
            }
            Vec3 finalColor = totalColor / scene.samplesPerPixel;
            int r = int(finalColor.x * 255);
            int g = int(finalColor.y * 255);
            int b = int(finalColor.z * 255);
            file << r << " " << g << " " << b << "\n";
        }
    }
    
    file.close();
    std::cout << "We are done !\n";
}

#endif /* Renderer_h */
