#include "Stars.h"

Bmp file("Sterne.BMP"); 

//width and heigth of the bmp
int width = file.getWidth();
int height = file.getHeight();
int numberofstars; //number of stars found in the picture

int main() 
{ 
//- PICTURE RECOGNITION ---

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
    numberofstars = marker.getNumberOfStars();
    delete[] digitalImage; 

    //calculate all the focus points 
    Pointf** focuspoints = Roi::focuspoints(grayscaledImage, width, stars,numberofstars);
    delete[] grayscaledImage; 

//- DATABASE SETUP ---

    Database stardb("hip_red_1.txt"); 
    Triangles triangledb(stardb);

//- STAR IDENTIFICATION ---

    //fining middlest point in the picture
    Pointf* middlest = Identifier::findmiddlest(focuspoints, numberofstars, width, height); 

    //calculating alpha1, alpha2 and beta angles
    Angles* angles = Identifier::angles(middlest, focuspoints, numberofstars);

    //calculating the best triangle
    Triangle bestFit = Identifier::bestfit(triangledb, stardb.size(), angles);

    printf("Angles found in the picture:\nalpha1\t\talpha2\t\tbeta\n");
    printf("%f\t%f\t%f\n", radiansToDegrees(angles->alpha1), radiansToDegrees(angles->alpha2), radiansToDegrees(angles->beta));
    
    printf("Best fit found:\n%f\t%f\t%f", radiansToDegrees(bestFit.alpha1), radiansToDegrees(bestFit.alpha2), radiansToDegrees(bestFit.beta));
    printf(" with ID1: %d\tID2: %d\tID3: %d\n", bestFit.id1.id, bestFit.id2.id, bestFit.id3.id);



}