//
//  Material.h
//  MyVec3
//
//  Created by Ivan Kuznetsov on 31.05.2026.
//

#ifndef Material_h
#define Material_h

#include "Vec3.h"

struct Material {
    Vec3 albedo;
    double reflectionRate;
    
    
    Material(Vec3 albedo, double reflectionRate) : albedo(albedo), reflectionRate(reflectionRate) {}
};


#endif /* Material_h */
