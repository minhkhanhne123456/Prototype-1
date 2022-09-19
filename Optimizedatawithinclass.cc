#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>
#include <iterator>
#include <cstdint>
#include "Optimizedatawithinclass.h"
using namespace std;

static int number_of_lines;

template <size_t N>
//Split string and add to array
void splitString(string (&arr)[N], string str)
{
    int n = 0;
    istringstream iss(str);
    for (auto it = istream_iterator<string>(iss); it != istream_iterator<string>() && n < N; ++it, ++n)
        arr[n] = *it;
}


int main()
    {
    ifstream in("CAN_config1.txt");
    string line1;
    
    while (getline (in, line1))
    {
        
        string splitdata[8];
        string split = "" + line1;
        splitString(splitdata,split);
        //Explicit type conversion
        unsigned int canidconvert = stoi(splitdata[0]);
        unsigned int canlengthconvert = stoi(splitdata[1]);
        unsigned int startbitconvert = stoi(splitdata[3]);
        unsigned int lengthconvert = stoi(splitdata[4]);
        double scaleconvert = stod(splitdata[5]);
        double offsetconvert = stod(splitdata[6]);
        bool endian = false;
        //Check the split data
        /*cout << canidconvert << " " << canlengthconvert << " " << splitdata[2] << " " << startbitconvert << " " << lengthconvert << " " <<
        offsetconvert << " " << splitdata[7] << endl;
         canlengthconvert;
        */

        control::canconfigure[number_of_lines].canid = canidconvert;
        control::canconfigure[number_of_lines].canlength = canlengthconvert;
        control::canconfigure[number_of_lines].name_variables = splitdata[2];
        control::canconfigure[number_of_lines].startbit = startbitconvert;
        control::canconfigure[number_of_lines].length = lengthconvert;
        control::canconfigure[number_of_lines].scale = scaleconvert;
        control::canconfigure[number_of_lines].offset = offsetconvert;
        control::canconfigure[number_of_lines].isBigendian = endian;

        cout << control::canconfigure [number_of_lines].canid << " ";
        cout << control::canconfigure [number_of_lines].canlength << " ";
        cout << control::canconfigure [number_of_lines].name_variables << " ";
        cout << control::canconfigure [number_of_lines].startbit << " ";
        cout << control::canconfigure [number_of_lines].length << " ";
        cout << control::canconfigure [number_of_lines].scale << " ";
        cout << control::canconfigure [number_of_lines].offset << " ";
        cout << control::canconfigure [number_of_lines].isBigendian << endl;
        
        number_of_lines++;
    }
    return 0;
    }
