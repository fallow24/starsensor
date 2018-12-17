#include "Stars.h"

<<<<<<< HEAD
//Hallo Fabi
=======
//Hallo Nils
>>>>>>> c11fb94920a7c324754cd9a8174ef0ac5cc13584

//sooooso

Bmp file("Sterne.BMP"); 
Database stardb("hip_red_1.txt"); 
Triangles triangledb(stardb);

//width and heigth of the bmp
int width = file.getWidth();
int height = file.getHeight();

int main() 
{ 
    //reading rgb values from BMP file
    unsigned char* rgbImage = file.readRGB();

    //convert the rgb image to grayscale (black-white image)
    int* grayscaledImage = file.grayscaleFromRGB(rgbImage); 
    delete[] rgbImage;

    /*
     * convert the grayscaled image into a binary image:
     * 1 represents a star
     * 0 represents space
     */
    int* digitalImage = file.digitalize(grayscaledImage);

    
    //recognition of stars in the digitalized (binary) image
    SeqReg marker; 
    std::vector<Point*> *stars = marker.classify(digitalImage, width, height); 
    delete[] digitalImage; 

    //calculate all the focus points 
    Pointf** focuspoints = Roi::focuspoints(grayscaledImage, width, stars, marker.getNumberOfStars());
    delete[] grayscaledImage; 

    //fining middlest point
    Pointf* middlest = Identifier::findmiddlest(focuspoints, marker.getNumberOfStars(), width, height); 

    printf("%d\n", marker.getNumberOfStars());

    for(int i = 0; i < marker.getNumberOfStars(); i++)
    {
        printf("Point %d = (%f, %f)\n", i, focuspoints[i]->x, focuspoints[i]->y);
    }

    printf("Middlest: Point = (%f, %f)\n", middlest->x, middlest->y);
    
}