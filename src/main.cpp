#include "Stars.h"

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

    //calculating all angles
    float angles[marker.getNumberOfStars() - 1];
    for(int i = 0; i < marker.getNumberOfStars(); i++)
    {   
        
        float dotproduct = middlest->x * focuspoints[i]->x + middlest->y * focuspoints[i]->y;
        float abss1 = sqrt(middlest->x * middlest->x + middlest->y * middlest->y);
        float abss2 = sqrt(focuspoints[i]->x * focuspoints[i]->x + focuspoints[i]->y * focuspoints[i]->y);
        angles[i] = acos(dotproduct / (abss1 * abss2));
        

    }

    for(int i = 0; i < marker.getNumberOfStars() - 1; i++) {
        printf("Angle %d: %f\n", i , angles[i]);
    }

    printf("%d\n", marker.getNumberOfStars());

    for(int i = 0; i < marker.getNumberOfStars(); i++)
    {
        printf("Point %d = (%f, %f)\n", i, focuspoints[i]->x, focuspoints[i]->y);
    }

    printf("Middlest: Point = (%f, %f)\n", middlest->x, middlest->y);
    
}