#ifndef BMP_H
#define BMP_H
#include "stdio.h"
/*
 * grayscale value from 0 to 255
 * a star gets recognized if grayscale > THRESHOLD
 */
#define THRESHOLD 21 //threshold for star recognizion

class Bmp
{
    private: 
        FILE* f;
        const char* filename;
        int width, height;
        unsigned char grayscale(unsigned char r, unsigned char g, unsigned char b);

    public:
        Bmp(const char* filename) { 
            this->filename = filename;
            f = fopen(filename, "rb");
            unsigned char info[54];
            fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

            // extract image height and width from header
            width = *(int*)&info[18];
            height = *(int*)&info[22];
        }

        unsigned char* readRGB();
        int* grayscaleFromRGB(unsigned char* rgb);
        int* digitalize(int* gray);
        int getWidth();
        int getHeight();

};

#endif