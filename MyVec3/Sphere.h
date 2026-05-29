//
//  Sphere.h
//  MyVec3
//
//  Created by Ivan Kuznetsov on 27.05.2026.
//

#ifndef Sphere_h
#define Sphere_h

#include <cmath>
#include <iostream>
#include "Vec3.h"
#include "Ray.h"

struct Sphere{
    Vec3 center;
    double radius;
    
    Sphere(Vec3 center, double radius) : center(center), radius(radius) {}
    
    double hit(const Ray& ray) const {
        double a = ray.direction.dot(ray.direction); //  масштаб кроку променя
        double b = 2 * (ray.origin - center).dot(ray.direction); // чи летить до сфери чи від неї
        double c = (ray.origin - center).dot(ray.origin - center) - radius * radius; // де стартує промінь відносно сфери
        double D = b * b - 4 * a * c; // чи влучив він в неї
        
        if (D < 0) {
            return -1.0;
        }
        
        double t1 = (-b - sqrt(D)) / (2 * a); // точка влучання ближче до камери
        
        return t1;

    }
};


#endif /* Sphere_h */
