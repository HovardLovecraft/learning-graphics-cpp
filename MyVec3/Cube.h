//
//  Cube.h
//  MyVec3
//
//  Created by Ivan Kuznetsov on 08.06.2026.
//

#ifndef Cube_h
#define Cube_h

#include <vector>
#include "Vec3.h"
#include "Triangle.h"

struct Cube {

    std::vector<Triangle> triangles;

    Cube(Vec3 A, Vec3 B, Vec3 C, Vec3 D, Vec3 E, Vec3 F, Vec3 G, Vec3 H)
    {
        
        triangles.reserve(12);

        // front
        Triangle tf1 = {B, C, E};
        Triangle tf2 = {C, D, E};
        triangles.emplace_back(tf1);
        triangles.emplace_back(tf2);

        // back
        Triangle tb1 = {A, G, F};
        Triangle tb2 = {A, H, G};
        triangles.emplace_back(tb1);
        triangles.emplace_back(tb2);

        // left
        Triangle tl1 = {A, B, E};
        Triangle tl2 = {F, B, A};
        triangles.emplace_back(tl1);
        triangles.emplace_back(tl2);

        //right
        Triangle tr1 = {G, H, D};
        Triangle tr2 = {G, D, C};
        triangles.emplace_back(tr1);
        triangles.emplace_back(tr2);

        // upper
        Triangle tu1 = {A, E, D};
        Triangle tu2 = {A, D, H};
        triangles.emplace_back(tu1);
        triangles.emplace_back(tu2);

        // lower
        Triangle tlw1 = {F, G, C};
        Triangle tlw2 = {F, C, B};
        triangles.emplace_back(tlw1);
        triangles.emplace_back(tlw2);
    }
};

#endif /* Cube_h */
