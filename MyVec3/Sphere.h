//
//  Sphere.h
//  MyVec3
//
//  Created by Ivan Kuznetsov on 27.05.2026.
//

#ifndef Sphere_h
#define Sphere_h

#include "Vec3.h"
#include "Ray.h"

struct Sphere{
    Vec3 center;
    double radius;
    
    Sphere(Vec3 center, double radius) : center(center), radius(radius) {}
    
    bool hit(const Ray& ray) const {
        double a = ray.direction.dot(ray.direction);
        double b = 2 * (ray.origin - center).dot(ray.direction);
        double c = (ray.origin - center).dot(ray.origin - center) - radius * radius;
        double D = b * b - 4 * a * c;
        
        return (D >= 0);

    }
};


#endif /* Sphere_h */
