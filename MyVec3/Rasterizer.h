//
//  Rasterizer.h
//  MyVec3
//
//  Created by Ivan Kuznetsov on 08.06.2026.
//

#ifndef Rasterizer_h
#define Rasterizer_h

#include "Cube.h"
#include "Framebuffer.h"
#include "Mat4.h"
#include "Vec4.h"

void rasterize(Framebuffer& fb, const Cube& cube, const Mat4& MVP, Vec3 cameraPos) {
    Vec4 v1;
    Vec4 v2;
    Vec4 v3;

    //triange area lambda function
    auto edgeFunc = [](int ax, int ay, int bx, int by, int cx, int cy) {
        return (bx - ax) * (cy - ay) - (by - ay) * (cx - ax);
    };
    
    for (Triangle t : cube.triangles) {
        
        //transform each vertex
        v1 = MVP.transform(t.A, 1.0);
        v2 = MVP.transform(t.B, 1.0);
        v3 = MVP.transform(t.C, 1.0);

        //perspective
        double p1x = v1.x / v1.w;
        double p1y = v1.y / v1.w;
        double p1z = v1.z / v1.w;

        double p2x = v2.x / v2.w;
        double p2y = v2.y / v2.w;
        double p2z = v2.z / v2.w;

        double p3x = v3.x / v3.w;
        double p3y = v3.y / v3.w;
        double p3z = v3.z / v3.w;


        // viewport transform
        int screen_x1 = int((p1x + 1) / 2 * fb.width);
        int screen_y1 = int((1 - p1y) / 2 * fb.height);
        
        int screen_x2 = int((p2x + 1) / 2 * fb.width);
        int screen_y2 = int((1 - p2y) / 2 * fb.height);
        
        int screen_x3 = int((p3x + 1) / 2 * fb.width);
        int screen_y3 = int((1 - p3y) / 2 * fb.height);

        // bounding box
        int minX = std::max(0, std::min(screen_x1, std::min(screen_x2, screen_x3)));
        int minY = std::max(0, std::min(screen_y1, std::min(screen_y2, screen_y3)));
        int maxX = std::min(fb.width - 1, std::max(screen_x1, std::max(screen_x2, screen_x3)));
        int maxY = std::min(fb.height - 1, std::max(screen_y1, std::max(screen_y2, screen_y3)));

        double totalArea = edgeFunc(screen_x1, screen_y1, screen_x2, screen_y2, screen_x3, screen_y3);
        Vec3 lightDir = cameraPos.normalize();
        double ambient = 0.15;
        double diffuse = std::max(0.0, t.normal.dot(lightDir));

        Vec3 centroid = (t.A + t.B + t.C) / 3.0;
        Vec3 V = (cameraPos - centroid).normalize();
        Vec3 R = t.normal * (2.0 * t.normal.dot(lightDir)) - lightDir;
        Vec3 H = (lightDir + V).normalize();
        double spec = pow(std::max(0.0, t.normal.dot(H)), 8.0);
        double brightness = ambient + 0.6 * diffuse + 0.4 * spec;

        for (int i = minY; i <= maxY; ++i){
            for (int j = minX; j <= maxX; ++j){
                
                double w1 = edgeFunc(j, i, screen_x2, screen_y2, screen_x3, screen_y3) / totalArea;
                double w2 = edgeFunc(screen_x1, screen_y1,  j, i,  screen_x3, screen_y3) / totalArea;
                double w3 = edgeFunc(screen_x1, screen_y1, screen_x2, screen_y2, j, i) / totalArea;

                if (w1 >= 0 && w2 >= 0 && w3 >= 0){
                    double depth = w1 * p1z + w2 * p2z + w3 * p3z;
                    fb.setPixel(j, i, Vec3{brightness, brightness, brightness}, depth);
                }
            }
        }

    }
    
}


#endif /* Rasterizer_h */
