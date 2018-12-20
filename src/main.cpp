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

//- CALCULATING ORIENTATION ---

    //getting starvectors in the sensorframe
    vectorTuple sensorframe = Position::calcStarVecs(m, a1, width, height);
    
    //getting starvectors in the ECI-Frame
    vectorTuple eciframe;

    Star m_star = bestFit.id1; //extracting the middlest star from the bestfit triangle
    Star a1_star = bestFit.id2; //extracting the nearest star from the bestfit triangle
    Vec3D eci_m(m_star.x, m_star.y, m_star.z);
    Vec3D eci_a1(a1_star.x, a1_star.y, a1_star.z);

    eciframe.v1 = eci_m;
    eciframe.v2 = eci_a1;

    //calculating rotation matrix with sensorframe and ECI-Frame vectors
    Matrix rotationMatrix = Position::calcRotationMatrix(sensorframe, eciframe);

    //calculating a quaternion from the rotation matrix
    Quaternion q = Position::rotToQuat(rotationMatrix);
    
//- PRINTING TO THE CONSOLE

    printf("\nStar m:\nx = %f, y = %f\n", m->x, m->y);
    
    printf("\nAngles found in the picture:\nalpha1\t\talpha2\t\tbeta\n");
    printf("%f\t%f\t%f\n", radiansToDegrees(angles->alpha1), radiansToDegrees(angles->alpha2), radiansToDegrees(angles->beta));
    
    printf("\nBest fit found in triangle database:\n%f\t%f\t%f", radiansToDegrees(bestFit.alpha1), radiansToDegrees(bestFit.alpha2), radiansToDegrees(bestFit.beta));
    printf("\tID1: %d\tID2: %d\tID3: %d\n", bestFit.id1.id, bestFit.id2.id, bestFit.id3.id);
    
    printf("\nSensorframe Vectors\nO_M:\nx: %f, y: %f, z: %f\n", sensorframe.v1.x, sensorframe.v1.y, sensorframe.v1.z);
    printf("O_A1:\nx: %f, y: %f, z: %f\n", sensorframe.v2.x, sensorframe.v2.y, sensorframe.v2.z);
    
    printf("\nRotationsmatix:\n");
    rotationMatrix.printMatrix();

    printf("\nQuaternion:");
    printf("\nq1 =\n\t[%f]\nq2 =\n\t[%f]\nq3 =\n\t[%f]\nq4 =\n\t[%f]\n", q.q0, q.q1, q.q2, q.q3);
    
}