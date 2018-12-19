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

    // for(int i = 0; i < numberofstars; i++)
    // {
    //     printf("Star #: %d\tx: %f\ty: %f\n", i, focuspoints[i]->x, focuspoints[i]->y);
    // }

    /*
     * TODO: @Nils Lagebestimmung
     * 'bestFit' ist ein 'Triangle' und enthält die 3 Sterne und die Winkel alpha1, alpha2 und beta. 
     * Die 3 Sterne sind vom Typ 'Star' und enthalten die ID des Sterns und die x, y & z Komponente des
     * Einheitsvektores im ECI-Frame.
     * Ausserdem gibt es die Punkte 'm', 'a1' und 'a2' vom Typ 'Pointf*'.
     * Die Punkte enthalten enthalten die x und y Koordinaten der Pixel der drei Sterne auf dem Bildsensor.
     * Der Punkt 'm' ist der mittlere, a1 ist der Punkt mit Winkel alpha1 und a2 der Punkt mit Winkel alpha2.
     * Der Ursprung des Koordinatensystems auf dem Bildsensor ist (0, 0) und liegt unten links.
     * Die x-Achse geht nach links, die y-Achse nach oben. 
     */

    printf("Angles found in the picture:\nalpha1\t\talpha2\t\tbeta\n");
    printf("%f\t%f\t%f\n", radiansToDegrees(angles->alpha1), radiansToDegrees(angles->alpha2), radiansToDegrees(angles->beta));
    // printf("Star 1: x = %f, y = %f\n", m->x, m->y);
    // printf("Star 2: x = %f, y = %f\n", a1->x, a1->y);
    // printf("Star 3: x = %f, y = %f\n", a2->x, a2->y);
    
    printf("Best fit found:\n%f\t%f\t%f", radiansToDegrees(bestFit.alpha1), radiansToDegrees(bestFit.alpha2), radiansToDegrees(bestFit.beta));
    printf(" with ID1: %d\tID2: %d\tID3: %d\n", bestFit.id1.id, bestFit.id2.id, bestFit.id3.id);

    // Star s;
    // for(int i = 0; i < stardb.size(); i++)
    // {
    //     s = stardb.stardata()[i];
    //     printf("Id: %d, x %f, y %f, z %f, mag %f\n", s.id, s.x, s.y, s.z, s.magnitude);
    // }
    // Triangle t;
    // for(int i = 0; i < stardb.size(); i++) 
    // {
    //     t = triangledb.data()[i];
    //     printf("ID1: %d\tID2: %d\tID3: %d\tA1: %f\tA2: %f\tB: %f\n", t.id1.id, t.id2.id, t.id3.id, radiansToDegrees(t.alpha1), radiansToDegrees(t.alpha2), radiansToDegrees(t.beta));
    // }

}