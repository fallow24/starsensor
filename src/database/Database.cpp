#include "Database.h"

string Database::readFromFile()
{
    //determine size of the database
    ifstream file_s(filename); //setting up a filestream
    string buf;
    int s = 0; //size of the database
    while(getline(file_s, buf)) s++; //iterating each line of the filestream

    //setting up the database
    ifstream file(filename);
    string str; //buffer used to store one string
    string file_contents, buffer; //file_contents: the whole database as a string
    //string buffer: buffer used to store one line of string
    double magnitude;

    //filling the database
    for (int i = 0; i < s; i++)
    {
        buffer = "";
        for(int j = 0; j < 4; j++)
        {
            if(j != 3) getline(file, str, ' ');
            else getline(file, str);
            buffer += str;
            buffer.push_back(' ');
            if(j == 3) 
            {
                magnitude = stof(str);
                if(magnitude <= MAX_MAGNITUDE) {
                    file_contents += buffer;
                    file_contents.push_back('\n');
                }
            } 
        }
        
    } 

    return file_contents;
}

string Database::strdata()
{
    return data;
}

Star* Database::str2db()
{
    //determine size of the database
    istringstream str_s(data); //setting up a stringstream
    string buf;
    int s = 0; //size of the database
    while(getline(str_s, buf)) s++; //iterating each line of the stringstream


    //setting up the database
    Star* db = new Star[s];
    values = s;
    istringstream f(data);
    string line, token, delimiter = " ";
    double rek, dek, e = degreesToRadians(23.44); //rektaszension und deklenation, e = schiefe der ekliptik
    
    //filling the database
    int i = 0, j = 0;
    while(getline(f, line))
    {
        size_t pos = 0;
        j = 0;
        while ((pos = line.find(delimiter)) != string::npos) {
            token = line.substr(0, pos);
            
            switch(j)
            {
                case 0: db[i].id = stoi(token); break;
                case 1: rek = stof(token); break;
                case 2: dek = stof(token); break;
                case 3: db[i].magnitude = stof(token); break;
            }

            line.erase(0, pos + delimiter.length());
            j++;
        }
        //printf("ID %d, REK %f, DEK %f, MAG %f\n", db[i].id, rek, dek, db[i].magnitude);

        //conversion from deg to rad
        rek = degreesToRadians(rek);
        dek = degreesToRadians(dek);
        //conversion from rek dek to x y z
        db[i].x = sin(e) * sin(dek) + cos(e) * cos(dek) * sin(rek);
        db[i].y = cos(dek) * cos(rek);
        db[i].z = cos(e) * sin(dek) - sin(e) * cos(dek) * sin(rek);
        i++;
    }

    return db;
}

double Database::anglebetween(Star s1, Star s2)
{
    double dotproduct = s1.x * s2.x + s1.y * s2.y + s1.z * s2.z;
    //double abss1 = sqrt(s1.x * s1.x + s1.y * s1.y + s1.z * s1.z);
    //double abss2 = sqrt(s2.x * s2.x + s2.y * s2.y + s2.z * s2.z);

    return acos(dotproduct);
}

double Database::calcbeta(Star s, Star t1, Star t2)
{
    double s_t1_x, s_t1_y, s_t1_z; //Vector S_T1
    double s_t2_x, s_t2_y, s_t2_z; //Vector S_T2

    //Vector S_T1
    s_t1_x = t1.x - s.x;
    s_t1_y = t1.y - s.y;
    s_t1_z = t1.z - s.z;

    //Vector S_T2
    s_t2_x = t2.x - s.x;
    s_t2_y = t2.y - s.y;
    s_t2_z = t2.z - s.z;

    double dotproduct = s_t1_x * s_t2_x + s_t1_y * s_t2_y + s_t1_z * s_t2_z;
    double abs_s_t1 = sqrt(s_t1_x * s_t1_x + s_t1_y * s_t1_y + s_t1_z * s_t1_z);
    double abs_s_t2 = sqrt(s_t2_x * s_t2_x + s_t2_y * s_t2_y + s_t2_z * s_t2_z);

    return acos(dotproduct / (abs_s_t1 * abs_s_t2));

}

Startuple* Database::findnearest(int index)
{
    Star reference = stars[index];
    double angle, lowestangle1 = 10000, lowestangle2 = 10000; //in rad (nothing can be bigger than 2PI)
    int index1 = 0, index2 = 0;

    for(int k = 0; k < values; k++)
    {
        if(index != k) {
            angle = (anglebetween(reference, stars[k]));

            if(angle < lowestangle1) {
                lowestangle2 = lowestangle1;
                index2 = index1;

                lowestangle1 = angle;
                index1 = k;
            } else if(angle < lowestangle2) {
                lowestangle2 = angle;
                index2 = k;
            }

        }

    } 

    Startuple* nearest = new Startuple;
    nearest->s1 = stars[index1];
    nearest->s2 = stars[index2];
    
    return nearest;
}

Star* Database::stardata() 
{
    return stars;
}

int Database::size()
{
    return values;
}

Star Database::getStarWithID(int ID) {
    for(int i = 0; i < values; i++) {
        Star current = stardata()[i];
        if(current.id == ID) return current; 
    }
}