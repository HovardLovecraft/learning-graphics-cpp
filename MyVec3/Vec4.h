//
//  Vec4.h
//  MyVec3
//
//  Created by Ivan Kuznetsov on 09.06.2026.
//

#ifndef Vec4_h
#define Vec4_h

struct Vec4 {
    double x, y, z, w;
    
    Vec4() : x(0.0), y(0.0), z(0.0), w(0.0) {}
    Vec4(double x, double y, double z, double w) : x(x), y(y), z(z), w(w) {}
};


#endif /* Vec4_h */
