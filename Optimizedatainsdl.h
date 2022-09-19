#ifndef _OPTIMIZEDATA_IN_SDL_H_
#define _OPTIMIZEDATA_IN_SDL_H_

#include <atomic>
#include <cstdint>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include "canconfigure.h"
#include <iostream>
using namespace std;

namespace sdl1 {
class VehicleServiceImpl1 {
public:
    template <size_t N>
    void splitString1(string (&arr)[N], string str);
    void loadData1();
};

}

#endif //_OPTIMIZEDATA_IN_SDL_H_