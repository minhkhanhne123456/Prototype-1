
#ifndef _CAN_CONFIGURE_H_
#define _CAN_CONFIGURE_H_

#include <cstdint>
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>

const int SIZE1 = 1000;

using namespace std;
namespace utils1 {

struct canConfigure1 {
    uint32_t canId1;         // number of CAN ID
    uint16_t canLength1;     // len`gth of frame in byte
    uint16_t startBit1;      // start bit
    uint16_t length1;        // length of value in bit
    string name_variables1;  // name of signals
    double scale1;           // scale value
    double offset1;          // offset value
    bool isBigendian1;       // true if bigendian
}canconfigure1[SIZE1];
}

#endif  // _CAN_CONFIGURE_H_