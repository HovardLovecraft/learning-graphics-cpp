//
//  Sphere.h
//  MyVec3
//
//  Created by Ivan Kuznetsov on 27.05.2026.
//

#ifndef Sphere_h
#define Sphere_h

#include <cmath>
#include "Vec3.h"
#include "Ray.h"
#include "Material.h"

struct Sphere{
    Vec3 center;
    Material material;
    double radius;
    
    Sphere(Vec3 center, Material material ,double radius) : center(center), material(material), radius(radius) {}
    
    double hit(const Ray& ray, double shadowAcne) const {
        Vec3 oc = ray.origin - center; // vector from sphere center to ray origin
        
        double a = ray.direction.dot(ray.direction); //  масштаб кроку променя
        double b = 2 * oc.dot(ray.direction); // чи летить до сфери чи від неї
        double c = oc.dot(oc) - radius * radius; // де стартує промінь відносно сфери
        double D = b * b - 4 * a * c; // чи влучив він в неї
        
        if (D < 0.0) {
            return -1.0;
        }
        
        double sqrtD = sqrt(D);
        
        
        double t1 = (-b - sqrtD) / (2 * a); // point of first hit
        if (t1 > shadowAcne) {
            return t1;
        }
        
        double t2 = (-b + sqrtD) / (2.0 * a); // point of farther hit
        if (t2 > shadowAcne) {
            return t2;
        }
        
        return -1.0;

    }
};


#endif /* Sphere_h */
