#include "SeqReg.h"

std::vector<Point*> * SeqReg::classify(int* pixels, int width, int height) {
    int neu = 1;
    //Suche ein Helles Pixel...
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++) {
            //wenn einer gefunden wurde:
            if (pixels[j * width + i] == 1) 
            {
                //potenzielle nachbarn am rand
                Point* validNeighbours = neighbour(i, j, width, height); //betrachte die nachbarn
                //für jeden nachbarn...   
                /*
                 * Es wird verglichen, ob der Nachbar schoneinmal betrachtet wurde.
                 * 
                 * Wenn der nachbar schonmal betrachtet wurde, ist sein inhalt groesser als 1.
                 * Dann gehoert der aktuell betrachtete pixel zur selben gruppe wie sein nachbar.
                 * 
                 * Wenn der Nachbar noch nicht betrachtet wurde, hat man einen neuen stern gefunden.
                 */ 
                if(validNeighbours[1].x != - 1 && pixels[validNeighbours[1].y * width + validNeighbours[1].x] > 1) {
                    pixels[j * width + i] = pixels[validNeighbours[1].y * width + validNeighbours[1].x];
                } else if (validNeighbours[2].x != - 1 && pixels[validNeighbours[2].y * width + validNeighbours[2].x] > 1) {
                    pixels[j * width + i] = pixels[validNeighbours[2].y * width + validNeighbours[2].x];
                } else if (validNeighbours[3].x != - 1 && pixels[validNeighbours[3].y * width + validNeighbours[3].x] > 1) {
                    pixels[j * width + i] = pixels[validNeighbours[3].y * width + validNeighbours[3].x];
                } else if (validNeighbours[4].x != - 1 && pixels[validNeighbours[4].y * width + validNeighbours[4].x] > 1) {
                    pixels[j * width + i] = pixels[validNeighbours[4].y * width + validNeighbours[4].x];
                } else if (validNeighbours[5].x != - 1 && pixels[validNeighbours[5].y * width + validNeighbours[5].x] > 1) {
                    pixels[j * width + i] = pixels[validNeighbours[5].y * width + validNeighbours[5].x];
                } else if (validNeighbours[6].x != - 1 && pixels[validNeighbours[6].y * width + validNeighbours[6].x] > 1) {
                    pixels[j * width + i] = pixels[validNeighbours[6].y * width + validNeighbours[6].x];
                } else if (validNeighbours[7].x != - 1 && pixels[validNeighbours[7].y * width + validNeighbours[7].x] > 1) {
                    pixels[j * width + i] = pixels[validNeighbours[7].y * width + validNeighbours[7].x];
                } else if (validNeighbours[8].x != - 1 && pixels[validNeighbours[8].y * width + validNeighbours[8].x] > 1) {
                    pixels[j * width + i] = pixels[validNeighbours[8].y * width + validNeighbours[8].x];
                } else {
                    //neuer stern gefunden
                    pixels[j * width + i] = ++neu;
                }
            }
        }
    }  

    numberOfStars = neu - 1; //determining size of star array

    /* stars is an array of vectors.
     * each vector contains the pixels that belong to one star.
     * the different array elements represent different stars.
     */
    //initialize the array of vectors
    std::vector<Point*> *stars = new std::vector<Point*>[numberOfStars];
    for(int i = 0; i < numberOfStars; i++) {
        stars[i] = *(new std::vector<Point*>);
    } 

    //fill the vectors in the array with the coordinate pixels of the stars
    int count;
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            count = pixels[j * width + i] - 2;
            if(count >= 0)
            {
                stars[count].push_back(new Point(i, j));
            }
        }
    }

    return stars;

}

int SeqReg::getNumberOfStars()
{
    return numberOfStars;
}

/*
 *   g f d
 *   h e c      e ist immer das Mittlere Element, a ist unten drunter
 *   i a b
 * 
 *   k ist die breite, j ist die hoehe
 */
Point* SeqReg::neighbour(int k, int j, int width, int height)
{   
    SeqReg::e = new Point(k, j); //mitte
    Point* undef = new Point(-1, -1); //ausserhalb des randes

    Point* neighbours = new Point[9];

    if(j - 1 >= 0) SeqReg::a = new Point(k, j - 1);
    else SeqReg::a = undef;

    if(k + 1 < width && j - 1 >= 0) SeqReg::b = new Point(k + 1, j - 1);
    else SeqReg::b = undef;

    if (k + 1 < width) SeqReg::c = new Point(k + 1, j);
    else SeqReg::c = undef;

    if (k + 1 < width && j + 1 < height) SeqReg::d = new Point(k + 1, j + 1);
    else SeqReg::d = undef;

    if (j + 1 < height) SeqReg::f = new Point(k, j + 1);
    else SeqReg::f = undef; 

    if (k - 1 >= 0 && j + 1 < height) SeqReg::g = new Point(k - 1, j + 1);
    else SeqReg::g = undef;

    if (k - 1 >= 0) SeqReg::h = new Point(k - 1, j);
    else SeqReg::h = undef;

    if(k - 1 >= 0 && j - 1 >= 0) SeqReg::i = new Point(k - 1, j - 1);
    else SeqReg::i = undef;

    neighbours[0] = *SeqReg::e;
    neighbours[1] = *SeqReg::a;
    neighbours[2] = *SeqReg::b;
    neighbours[3] = *SeqReg::c;
    neighbours[4] = *SeqReg::d;
    neighbours[5] = *SeqReg::f;
    neighbours[6] = *SeqReg::g;
    neighbours[7] = *SeqReg::h;
    neighbours[8] = *SeqReg::i;

    return neighbours;
}