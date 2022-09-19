#ifndef _OPTIMIZE_DATA_WITHIN_CLASS_
#define _OPTIMIZE_DATA_WITHIN_CLASS_

#include <cstdint>
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;
const int SIZE = 1000;

namespace control{
struct canconfigure1 {
    uint32_t canid;
    uint16_t canlength; 
    string name_variables; 
    uint16_t startbit;    
    uint16_t length;      
    double scale;          
    double offset;
    bool isBigendian;
}canconfigure[SIZE];
};

#endif  // _OPTIMIZE_DATA_WITHIN_CLASS_