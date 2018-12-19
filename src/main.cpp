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

    Identifier identifier;
    //fining middlest point in the picture
    Pointf* m = identifier.findmiddlest(focuspoints, numberofstars, width, height); 

    //calculating alpha1, alpha2 and beta angles
    Angles* angles = identifier.angles(m, focuspoints, numberofstars);
    Pointf *a1 = identifier.geta1(), *a2 = identifier.geta2(); //nearest points

    //calculating the best triangle
    Triangle bestFit = identifier.bestfit(triangledb, stardb.size(), angles);

// - CALCULATING ORIENTATION ---

    vectorTuple sensorframe = Position::calcStarVecs(m, a1, width, height);
    vectorTuple eciframe;

    Star m_star = bestFit.id1;
    Star a1_star = bestFit.id2;

    Vec3D eci_m(m_star.x, m_star.y, m_star.z);
    Vec3D eci_a1(a1_star.x, a1_star.y, a1_star.z);

    eciframe.v1 = eci_m;
    eciframe.v2 = eci_a1;

    Matrix rotationMatrix = Position::calcRotationMatrix(sensorframe, eciframe);

    printf("Angles found in the picture:\nalpha1\t\talpha2\t\tbeta\n");
    printf("%f\t%f\t%f\n", radiansToDegrees(angles->alpha1), radiansToDegrees(angles->alpha2), radiansToDegrees(angles->beta));
    // printf("Star 1: x = %f, y = %f\n", m->x, m->y);
    // printf("Star 2: x = %f, y = %f\n", a1->x, a1->y);
    // printf("Star 3: x = %f, y = %f\n", a2->x, a2->y);
    
    printf("Best fit found:\n%f\t%f\t%f", radiansToDegrees(bestFit.alpha1), radiansToDegrees(bestFit.alpha2), radiansToDegrees(bestFit.beta));
    printf(" with ID1: %d\tID2: %d\tID3: %d\n", bestFit.id1.id, bestFit.id2.id, bestFit.id3.id);
    
    printf("mx %f, my %f, mz %f\n", m_star.x, m_star.y, m_star.z);
    printf("a1 x %f, a1 y %f, a1 z %f\n", a1_star.x, a1_star.y, a1_star.z);

    rotationMatrix.printMatrix();

    Quaternion q = Position::rotToQuat(rotationMatrix);
    printf("\n[%f]\n[%f]\n[%f]\n[%f]", q.q0, q.q1, q.q2, q.q3);
}