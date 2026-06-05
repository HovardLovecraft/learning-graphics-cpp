//
//  Camera.h
//  MyVec3
//
//  Created by Ivan Kuznetsov on 27.05.2026.
//

#ifndef Camera_h
#define Camera_h

#include "Mat4.h"
#include "Vec3.h"
#include "Ray.h"

struct Camera{
    Vec3 eye;
    Vec3 forward;
    Vec3 right;
    Vec3 up;
    double fov;
    double aspect;
    double near;
    double far;
    
    //Prefered constructor
    Camera(Vec3 eye, Vec3 target, Vec3 upDir, double fov, double aspect, double near, double far)
    : eye(eye), fov(fov), aspect(aspect), near(near), far(far)
    {
        Mat4 view = Mat4::lookAt(eye, target, upDir);
        right   = Vec3{view.matrix[0][0], view.matrix[0][1], view.matrix[0][2]};
        up      = Vec3{view.matrix[1][0], view.matrix[1][1], view.matrix[1][2]};
        forward = Vec3{-view.matrix[2][0], -view.matrix[2][1], -view.matrix[2][2]};
    }
    
    Ray getRay(double u, double v) const {
        Vec3 dir = forward + right * (u - 0.5) + up * (v - 0.5);
        Ray ray{eye, dir};
        return ray;
    }
};

#endif /* Camera_h */
