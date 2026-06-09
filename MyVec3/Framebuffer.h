
#ifndef Framebuffer_h
#define Framebuffer_h


#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include "Vec3.h"


struct Framebuffer{
    int width, height;
    std::vector<Vec3> pixels;
    std::vector<double> depthBuffer;
    
    
    Framebuffer(int w, int h)
    : width(w), height(h), pixels(w * h, Vec3{0,0,0}), depthBuffer(w * h, std::numeric_limits<double>::infinity())  {}
    
    void setPixel(int x, int y, Vec3 color, double depth){
        
        if (depth < depthBuffer[y * width + x]) {
            pixels[y * width + x] = color;
            depthBuffer[y * width + x] = depth;
        }
    }
    
    void savePPM(const std::string& path){
        std::ofstream file(path);
        if (!file) {
            std::cerr << "Failed to open file!\n";
            return;
        }
        
        file << "P3\n";
        file << width << " " << height << "\n";
        file << "255\n";

        for (Vec3 p : pixels) {
            file 
            << int(std::min(1.0, std::max(0.0, p.x)) * 255) << " " 
            << int(std::min(1.0, std::max(0.0, p.y)) * 255) << " " 
            << int(std::min(1.0, std::max(0.0, p.z)) * 255) << "\n";
        }
        
        file.close();
        std::cout << "We are done !\n";
    }
};


#endif /* Framebuffer_h */
