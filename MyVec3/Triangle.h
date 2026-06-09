

#include "Vec3.h"

struct Triangle {
    Vec3 A, B, C;
    Vec3 normal;

    Triangle(Vec3 a, Vec3 b, Vec3 c) : A(a), B(b), C(c)
    {
        Vec3 ab{B.x - A.x, B.y - A.y, B.z - A.z};
        Vec3 ac{C.x - A.x, C.y - A.y, C.z - A.z};
        
        Vec3 n = ab.cross(ac);
        normal = n.normalize();
    }
};
