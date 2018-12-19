#include <stdio.h>
#include "Bmp.h"

unsigned char* Bmp::readRGB()
{
    printf("Read .bmp file... ");
    fflush(stdout);
    int size = 3 * width * height;
    unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel
    fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
    fclose(f);
    printf(" done!\n");
    fflush(stdout);

    return data; 
}

int* Bmp::grayscaleFromRGB(unsigned char* rgb)
{
    int* grayscaledImage = new int[width * height]; 
    
    printf("Converting .bmp file in grayscale...");
    fflush(stdout);
    unsigned char r, g, b;
    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            r = rgb[3 * (j * width + i)];
            g = rgb[3 * (j * width + i) + 1];
            b = rgb[3 * (j * width + i) + 2];
            grayscaledImage[j * width + i] = grayscale(r, g, b);
        }   
    }
    printf(" done!\n");
    fflush(stdout);
    
    return grayscaledImage;
}

int* Bmp::digitalize(int* gray)
{
    int* digitalImage = new int[width * height];

    printf("Converting grayscale to binary...");
    fflush(stdout);
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++) {
            if (gray[j * width + i] > THRESHOLD) digitalImage[j * width + i] = 1;
            else digitalImage[j * width + i] = 0;
        }
    }
    printf(" done!\n");
    fflush(stdout);

    return digitalImage;
}

unsigned char Bmp::grayscale(unsigned char r, unsigned char g, unsigned char b) 
{
    unsigned char gray;
    
    //grayscale = 0,299 × red + 0,587 × green + 0,114 × blue
    gray = 0.299 * r + 0.587 * g + 0.114 * b;
        
    return gray;
}

int Bmp::getWidth()
{
    return width;
}

int Bmp::getHeight()
{
    return height;
}