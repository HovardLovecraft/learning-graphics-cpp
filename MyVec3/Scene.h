//
//  Scene.h
//  MyVec3
//
//  Created by Ivan Kuznetsov on 04.06.2026.
//

#ifndef Scene_h
#define Scene_h

#include <vector>
#include "Camera.h"
#include "Vec3.h"
#include "Sphere.h"



struct Scene {
    int imageWidth;
    int imageHeight;
    int samplesPerPixel;
    int maxBounces;
    double ambient;
    double shadowAcne;
    Vec3 lightPosition;
    Camera camera;
    std::vector<Sphere> spheres;
    
    Scene(int imageWidth,
          int imageHeight,
          int samplesPerPixel,
          int maxBounces,
          double ambient,
          double shadowAcne,
          Vec3 lightPosition,
          Camera camera,
          std::vector<Sphere> spheres) :
    imageWidth(imageWidth),
    imageHeight(imageHeight),
    samplesPerPixel(samplesPerPixel),
    maxBounces(maxBounces),
    ambient(ambient),
    shadowAcne(shadowAcne),
    lightPosition(lightPosition),
    camera(camera),
    spheres(spheres)
    {}
};




#endif /* Scene_h */
