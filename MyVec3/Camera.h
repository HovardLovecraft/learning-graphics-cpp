//
//  Camera.h
//  MyVec3
//
//  Created by Ivan Kuznetsov on 27.05.2026.
//

#ifndef Camera_h
#define Camera_h

#include "Vec3.h"
#include "Ray.h"

struct Camera{
    Vec3 position;
    double viewportWidth;
    double viewportHeight;
    double focalLength;
    
    Camera(Vec3 position, double viewportWidth, double viewportHeight, double focalLength)
        : position(position),
          viewportWidth(viewportWidth),
          viewportHeight(viewportHeight),
          focalLength(focalLength) {}
    
    Ray getRay(double u, double v) const {
        Vec3 viewportPoint{-viewportWidth/2 + u * viewportWidth, -viewportHeight/2 + v * viewportHeight, -focalLength};
        Ray ray{{position}, {viewportPoint - position}};
        return ray;
    };
};

#endif /* Camera_h */
