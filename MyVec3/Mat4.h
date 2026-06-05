//
//  Mat4.h
//  MyVec3
//
//  Created by Ivan Kuznetsov on 04.06.2026.
//

#ifndef Mat4_h
#define Mat4_h

#include "Vec3.h"

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
 
    
    Vec3 transform(const Vec3& v, double w) const {
        Vec3 result;
        result.x = matrix[0][0]*v.x + matrix[0][1]*v.y + matrix[0][2]*v.z + matrix[0][3]*w;
        result.y = matrix[1][0]*v.x + matrix[1][1]*v.y + matrix[1][2]*v.z + matrix[1][3]*w;
        result.z = matrix[2][0]*v.x + matrix[2][1]*v.y + matrix[2][2]*v.z + matrix[2][3]*w;
        // четвертий рядок відкидаємо
        
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
};


#endif /* Mat4_h */
