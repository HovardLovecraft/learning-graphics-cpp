//
//  main.cpp
//  MyVec3
//
//  Created by Ivan Kuznetsov on 25.05.2026.
//

#include <iostream>
#include <fstream>
#include "Vec3.h"
#include "Ray.h"
#include "Sphere.h"
#include "Camera.h"
#include "Color.h"

int main(int argc, const char * argv[]) {
    
    const int imageWidth{80};
    const int imageHeight{60};
    const Camera cam{Vec3{0.0, 0.0, 1.5}, 3.0, 3.0, 3.0};
    const Sphere sphere{Vec3{0.0, 0.0, -5.0}, 1.0};
    
    std::ofstream file("output/image.ppm");
    if (!file) {
        std::cerr << "Failed to open file!\n";
        return 1;
    }
    
    file << "P3\n";
    file << imageWidth << " " << imageHeight << "\n";
    file << "255\n";
    
    for (int row{0}; row < imageHeight; ++row) {
        for (int col {0}; col < imageWidth; ++col) {
            double u = double(col / (imageWidth -1.0));
            double v = double(row / (imageHeight-1.0));
            Ray r = cam.getRay(u, v);
            
            if (sphere.hit(r)){
                //std::cout << " We have red at row " << row << " col " << col << "\n";
                //int red = col % 256;  // Red varies with x
//                int green = row % 256;  // Green varies with y
//                int blue = 128;      // Blue stays constant
                //file << red << " " << green << " " << blue << "  ";
                file << "255 0 0\n";
            } else {
                //std::cout << " We have blue at row " << row << " col " << col << "\n";
//                int red = 128;          // Red stays constant
//                int green = row % 256;  // Green varies with row
//                int blue = col % 256;      // Blue varies with col
//                file << red << " " << green << " " << blue << "  ";
                file << "0 0 255\n";
            }
        }
    }
    
    file.close();
    std::cout << "We are done !\n";
    
    
    //Tests TODO create real unit tests
//    std::cout << "Create Vec3 isntance!\n";
//    
//    Vec3 v{1.0, 2.0, 3.0};
//    
//    std::cout << v.x << "\n";
//    std::cout << v.y << "\n";
//    std::cout << v.z << "\n";
//    
//    std::cout << "Add" << "\n";
//    const Vec3 v1{1.0, 2.0, 3.0};
//    const Vec3 v2{4.0, 5.0, 6.0};
//    Vec3 addResult = v2 + v1;
//    
//    std::cout << addResult.x << "\n";
//    std::cout << addResult.y << "\n";
//    std::cout << addResult.z << "\n";
//    
//    
//    std::cout << "Subtract" << "\n";
//    Vec3 subtractResult = v2 - v1;
//    
//    std::cout << subtractResult.x << "\n";
//    std::cout << subtractResult.y << "\n";
//    std::cout << subtractResult.z << "\n";
//    
//    std::cout << "Dot" << "\n";
//    const Vec3 dotU{2.0, 2.0, 0.0};
//    const Vec3 dotV{2.0, 3.0, 0.0};
//    double dotResult = dotU.dot(dotV);
//    
//    std::cout << dotResult << "\n";
//    
//    std::cout << "Cross" << "\n";
//    const Vec3 u11{1.0, 0.0, 0.0};
//    const Vec3 v22{0.0, 1.0, 0.0};
//    
//    Vec3 crossResult = u11.cross(v22);
//    
//    std::cout << crossResult.x << "\n";
//    std::cout << crossResult.y << "\n";
//    std::cout << crossResult.z << "\n";
//    
//    std::cout << "Length" << "\n";
//    const Vec3 u22{3.0, 4.0, 5.0};
//    const Vec3 v33{6.0, 7.0, 8.0};
//    
//    double uLength = u22.length();
//    double vLength = v33.length();
//    std::cout << uLength << "\n";
//    std::cout << vLength << "\n";
//    
//    std::cout << "Normalize" << "\n";
//    Vec3 normU22 = u22.normalize();
//    Vec3 normV22 = v22.normalize();
//    
//    std::cout << "U22" << "\n";
//    std::cout << normU22.x << "\n";
//    std::cout << normU22.y << "\n";
//    std::cout << normU22.z << "\n";
//    std::cout << "V22" << "\n";
//    std::cout << normV22.x << "\n";
//    std::cout << normV22.y << "\n";
//    std::cout << normV22.z << "\n";
    
    
    
    
    

    
    
    
    
    
    
    
    return EXIT_SUCCESS;
}
