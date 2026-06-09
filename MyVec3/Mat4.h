//
//  Mat4.h
//  MyVec3
//
//  Created by Ivan Kuznetsov on 04.06.2026.
//

#ifndef Mat4_h
#define Mat4_h

#include <cmath>
#include "Vec3.h"
#include "Vec4.h"

struct Mat4 {
    double matrix[4][4];
    
    Mat4(){
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                if (row == col) {
                    matrix[row][col] = 1;
                } else {
                    matrix[row][col] = 0;
                }
            }
        }
    }
 
    
    Vec4 transform(const Vec3& v, double w) const {
        Vec4 result;
        result.x = matrix[0][0]*v.x + matrix[0][1]*v.y + matrix[0][2]*v.z + matrix[0][3]*w;
        result.y = matrix[1][0]*v.x + matrix[1][1]*v.y + matrix[1][2]*v.z + matrix[1][3]*w;
        result.z = matrix[2][0]*v.x + matrix[2][1]*v.y + matrix[2][2]*v.z + matrix[2][3]*w;
        result.w = matrix[3][0]*v.x + matrix[3][1]*v.y + matrix[3][2]*v.z + matrix[3][3]*w;
        
        return result;
    }

    static Mat4 translate(double tx, double ty, double tz) {
        
        Mat4 m;
        
        m.matrix[0][3] = tx;
        m.matrix[1][3] = ty;
        m.matrix[2][3] = tz;
        
        return m;
    }

    static Mat4 scale(double sx, double sy, double sz) {
        
        Mat4 m;
        
        m.matrix[0][0] = sx;
        m.matrix[1][1] = sy;
        m.matrix[2][2] = sz;
        
        return m;
    }

    static Mat4 zero() {
        
        Mat4 m;
        
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++){
                m.matrix[i][j] = 0.0;
            }
        }
        
        return m;      
    }

    Mat4 operator*(const Mat4& other) const {
        
        Mat4 m = Mat4::zero();

        for(int row{0}; row<4; ++row) {
            for(int col{0}; col < 4; ++col) {
                for (int k{0}; k < 4; ++k) {
                    m.matrix[row][col]+= matrix[row][k]*other.matrix[k][col];
                }
            }
        }

        return m;
    }

    static Mat4 lookAt(Vec3 eye, Vec3 target, Vec3 up) {
        
        Mat4 m;
        Vec3 forward = (target - eye).normalize();
        Vec3 right = forward.cross(up).normalize();
        Vec3 up_corrected = right.cross(forward);

        m.matrix[0][0] = right.x;
        m.matrix[0][1] = right.y;
        m.matrix[0][2] = right.z;
        m.matrix[0][3] = -right.dot(eye);
        m.matrix[1][0] = up_corrected.x;
        m.matrix[1][1] = up_corrected.y;
        m.matrix[1][2] = up_corrected.z;
        m.matrix[1][3] = -up_corrected.dot(eye);
        m.matrix[2][0] = -forward.x;
        m.matrix[2][1] = -forward.y;
        m.matrix[2][2] = -forward.z;
        m.matrix[2][3] = forward.dot(eye);
        m.matrix[3][0] = 0.0;
        m.matrix[3][1] = 0.0;
        m.matrix[3][2] = 0.0;
        m.matrix[3][3] = 1.0;

        return m;
    }

    static Mat4 perspective(double fov, double aspect, double near, double far) {
        
        Mat4 m = Mat4::zero();

        if (aspect == 0) return m;

        double f = 1/tan(fov* (M_PI / 180)/2);

        m.matrix[0][0] = f / aspect; // scaling point of view (Scale X)
        m.matrix[1][1] = f; // Scale Y
        m.matrix[2][2] = -(far+near)/(far-near); // This is needed by the GPU to know "how far away" each pixel is in the normalized space.
        m.matrix[2][3] = -2*far*near/(far-near); // This is needed by the GPU to know "how far away" each pixel is in the normalized space.
        m.matrix[3][2] = -1; // heart of perspective 

        return m;
    }
};


#endif /* Mat4_h */
