//
//  RayTracer.h
//  MyVec3
//
//  Created by Ivan Kuznetsov on 31.05.2026.
//

#ifndef RayTracer_h
#define RayTracer_h

#include <utility>
#include <vector>
#include "Sphere.h"

inline std::pair<double, const Sphere*> traceRay(const Ray& r, const std::vector<Sphere>& spheres, double shadowAcne){
    
    double closestT = -1.0;
    const Sphere* closestSphere = nullptr;
    
    for (const Sphere& s : spheres){
        
        // hit test
        double t = s.hit(r, shadowAcne); // ray parameter: distance along ray to hit point
        
        if (t > 0 && (closestT < 0 || t < closestT)){ //
            closestT = t;
            closestSphere = &s;
        }
    }
    
    return std::pair<double, const Sphere*>{closestT, closestSphere};
    
    
}

inline bool isInShadow(const Ray& shadowRay, const Vec3& lightPos, const std::vector<Sphere>& spheres, double shadowAcne) {
    
    Vec3 toLight = lightPos - shadowRay.origin;
    double distanceToLight = toLight.length();
    
    for (const Sphere& s : spheres) {
        double t = s.hit(shadowRay, shadowAcne);
        if (t > shadowAcne && t < distanceToLight){
            return true;
        }
    }
    
    return false;
}

#endif /* RayTracer_h */
