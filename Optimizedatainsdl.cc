#include <utility>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <canconfigure.h>
#include "Optimizedatainsdl.h"

static int number_of_lines;


using namespace std;

namespace sdl1 {
    template <size_t N>
    void VehicleServiceImpl1::splitString1(string (&arr)[N], string str)
    {   
    int n = 0;
    istringstream iss(str);
    for (auto it = istream_iterator<string>(iss); it != istream_iterator<string>() && n < N; ++it, ++n)
        arr[n] = *it;
    }

    void VehicleServiceImpl1::loadData1(){
    ifstream in("CAN_config1.txt");
    string line1;
    while (getline (in, line1))
    {
        string splitdata[8];
        string split = "" + line1;
        splitString1(splitdata,split);
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

        utils1::canconfigure1[number_of_lines].canId1 = canidconvert;
        utils1::canconfigure1[number_of_lines].canLength1 = canlengthconvert;
        utils1::canconfigure1[number_of_lines].name_variables1 = splitdata[2];
        utils1::canconfigure1[number_of_lines].startBit1 = startbitconvert;
        utils1::canconfigure1[number_of_lines].length1 = lengthconvert;
        utils1::canconfigure1[number_of_lines].scale1 = scaleconvert;
        utils1::canconfigure1[number_of_lines].offset1 = offsetconvert;
        utils1::canconfigure1[number_of_lines].isBigendian1 = endian;

        cout << utils1::canconfigure1 [number_of_lines].canId1 << " ";
        cout << utils1::canconfigure1 [number_of_lines].canLength1 << " ";
        cout << utils1::canconfigure1 [number_of_lines].name_variables1 << " ";
        cout << utils1::canconfigure1 [number_of_lines].startBit1 << " ";
        cout << utils1::canconfigure1 [number_of_lines].length1 << " ";
        cout << utils1::canconfigure1 [number_of_lines].scale1 << " ";
        cout << utils1::canconfigure1 [number_of_lines].offset1 << " ";
        cout << utils1::canconfigure1 [number_of_lines].isBigendian1 << endl;
        
        number_of_lines++;
    }
    }
}