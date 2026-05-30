//
//  main.cpp
//  MyVec3
//
//  Created by Ivan Kuznetsov on 25.05.2026.
//

#include <iostream>
#include <fstream>
#include "Vec3.h"
#include "Ray.h"
#include "Sphere.h"
#include "Camera.h"
#include "Color.h"

int main(int argc, const char * argv[]) {
    
    const int imageWidth{800};
    const int imageHeight{600};
    const double ambient = 0.25;
    const double shadowAcne = 0.001;
    const Camera cam{Vec3{0.0, 0.0, 1.5}, 3.0, 3.0, 3.0};
    const Sphere sphere{Vec3{0.0, 0.0, -7.0}, 0.5};
    const Sphere sphere2{Vec3{-0.8, 0.4, -5.5}, 0.3};
    const Sphere sphere3{Vec3{-1.4, 0.7, -4.0}, 0.1};
    std::vector<Sphere> spheres;
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
            double u = double(col / (imageWidth -1.0));
            double v = double(row / (imageHeight-1.0));
            Ray r = cam.getRay(u, v);
            double closestT = -1.0;
            const Sphere* closestSphere = nullptr;
            
            for (const Sphere& s : spheres){
 
                double t = s.hit(r); // ray parameter: distance along ray to hit point
                
                if (t > 0 && (closestT < 0 || t < closestT)){ //
                    closestT = t;
                    closestSphere = &s;
                }
            }
            
            if (closestT > 0) {
                Vec3 P = r.origin + r.direction * closestT; // point of hit
                Vec3 N = (P - closestSphere->center).normalize(); // normal
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
                
                
                double brightness;
                if (inShadow) {
                    brightness = ambient; 
                } else {
                    brightness = std::min(1.0, ambient + std::max(0.0, N.dot(lightDir))); // brightness is defined by cos of angle between normal and lightdir
                }
                int b = int(brightness * 255);
                Color color{b, b, b};
                file << color.r << " " << color.g << " " << color.b << "\n";
            } else {
                file << "0 0 255\n";
            }
        }
    }
    
    file.close();
    std::cout << "We are done !\n";
    
    return EXIT_SUCCESS;
}
