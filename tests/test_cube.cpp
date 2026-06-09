#include "doctest.h"
#include "Cube.h"

TEST_CASE("Validate cube consists of 12 triangles"){
    
    Cube cube{
        Vec3{-0.5, 0.5, -0.5},
        Vec3{-0.5, -0.5, 0.5},
        Vec3{0.5, -0.5, 0.5},
        Vec3{0.5, 0.5, 0.5}, 
        Vec3{-0.5, 0.5, 0.5}, 
        Vec3{-0.5, -0.5, -0.5}, 
        Vec3{0.5, -0.5, -0.5,}, 
        Vec3{0.5, 0.5, -0.5}
    };

    CHECK(cube.triangles.size() == 12);
}