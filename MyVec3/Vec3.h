//
//  Vec3.h
//  MyVec3
//
//  Created by Ivan Kuznetsov on 25.05.2026.
//

#ifndef Vec3_h
#define Vec3_h

#include <cmath>

struct Vec3 {
    double x, y, z;
    
    Vec3() : x(0.0), y(0.0), z(0.0) {}
    Vec3(double x, double y,double z) : x(x), y(y), z(z) {}
    
    //    add
    Vec3 operator+(const Vec3& otherVec) const {
        return Vec3{x + otherVec.x, y + otherVec.y, z + otherVec.z};
    }
    
    //    subtract
    Vec3 operator-(const Vec3& otherVec) const {
        return Vec3{x - otherVec.x, y - otherVec.y, z - otherVec.z};
    }
    
    Vec3 operator*(double scalar) const {
        return {x * scalar, y * scalar, z * scalar};
    }

    Vec3 operator/(double scalar) const {
        return {x / scalar, y / scalar, z / scalar};
    }
    
    //    dot
    double dot (const Vec3& otherVec) const {
        return (x * otherVec.x) + (y * otherVec.y) + (z * otherVec.z);
    }
    //    cross
    Vec3 cross (const Vec3& otherVec) const {
        return Vec3{
            y * otherVec.z - z * otherVec.y,
            z * otherVec.x - x * otherVec.z,
            x * otherVec.y - y * otherVec.x
        };
    }
    //    length
    double length () const {
        return std::sqrt(x * x + y * y + z * z);
    }
    //    normalize
    Vec3 normalize() const  {
        double len = length();

        if (len < 1e-8) {
            return {0.0, 0.0, 0.0};
        }

        return {x / len, y / len, z / len};
    };
};


#endif /* Vec3_h */
