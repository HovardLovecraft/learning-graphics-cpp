//
//  Ray.h
//  MyVec3
//
//  Created by Ivan Kuznetsov on 27.05.2026.
//

#ifndef Ray_h
#define Ray_h

#include "Vec3.h"

struct Ray{
    Vec3 origin, direction;
    
    Ray(Vec3 origin, Vec3 direction) : origin(origin), direction(direction) {}
};


#endif /* Ray_h */
