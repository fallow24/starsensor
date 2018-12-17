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

    printf("Angles found in the picture:\nalpha1\t\talpha2\t\tbeta\n");
    printf("%f\t%f\t%f\n", radiansToDegrees(angles->alpha1), radiansToDegrees(angles->alpha2), radiansToDegrees(angles->beta));
    
    // Triangle t;
    // for(int i = 0; i< stardb.size(); i++)
    // {
    //     t = triangledb.data()[i];
    //     printf("Id1 %d\tId2 %d\tId3 %d\ta1 %f\ta2 %f\tb %f\n",t.id1.id, t.id2.id, t.id3.id, t.alpha1, t.alpha2, t.beta);
    // }

    //searching for the angles in the database
    float e, e_a1, e_a2, e_b, e_min = 10000000;
    Triangle tmp, bestFit;
    for(int i = 0; i < stardb.size(); i++)
    {
        tmp = triangledb.data()[i];
        e_a1 = (tmp.alpha1 - angles->alpha1);
        e_a2 = (tmp.alpha2 - angles->alpha2);
        e_b = (tmp.beta - angles->beta);
        e = sqrt(e_a1*e_a1 + e_a2*e_a2 + e_b*e_b);
        if(abs(e) < e_min) {
            e_min = abs(e);
            bestFit = tmp;
        }

    }

    printf("Best fit found:\n%f\t%f\t%f", radiansToDegrees(bestFit.alpha1), radiansToDegrees(bestFit.alpha2), radiansToDegrees(bestFit.beta));
    printf(" with ID1: %d\tID2: %d\tID3: %d", bestFit.id1.id, bestFit.id2.id, bestFit.id3.id);



}