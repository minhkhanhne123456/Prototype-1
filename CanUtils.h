#ifndef _SDL_UTILS_CAN_UTILS_H_
#define _SDL_UTILS_CAN_UTILS_H_

#include <cstdint>

namespace utils {

struct canConfigure {
    uint32_t canId;         // number of CAN ID
    uint16_t canLength;     // length of frame in byte
    uint8_t startBit;       // start bit
    uint16_t length;        // length of value in bit
    double scale;           // scale value
    double offset;          // offset value
    bool isBigendian;       // true if bigendian
};

/* @brief get parking status from CAN frame
*  @param[in] inCanConfig Can Configure of the value need to get
*  @param[in] inFrame data frame
*  @param[in] outValue output data
*/
uint8_t getCanValue(canConfigure inCanConfig, uint64_t inFrame, double& outValue);

/* @brief convert CAN frame to little endian
*  @param[in] inFrame data to swap
*
*  if raw CAN data is presented as big endian, convert to little endian
*  before calling getSpeed, getVoltage, getMileage, isSideStand,...
*/
uint64_t convertCanFrameToLittleEndian(uint64_t inFrame);

/* @brief convert 64-bit CAN frame to little endian
*  @param[in] inFrame data to swap
*
*  if raw CAN data is presented as big endian, convert to little endian
*  before calling getSpeed, getVoltage, getMileage, isSideStand,...
*/
uint64_t convertCanFrameToLittleEndian64(uint64_t inFrame);

/* @brief convert 56-bit CAN frame to little endian
*  @param[in] inFrame data to swap
*
*  if raw CAN data is presented as big endian, convert to little endian
*  before calling getSpeed, getVoltage, getMileage, isSideStand,...
*/

uint64_t convertCanFrameToLittleEndian56(uint64_t inFrame);

/* @brief convert 48-bit CAN frame to little endian
*  @param[in] inFrame data to swap
*
*  if raw CAN data is presented as big endian, convert to little endian
*  before calling getSpeed, getVoltage, getMileage, isSideStand,...
*/
uint64_t convertCanFrameToLittleEndian48(uint64_t inFrame);

/* @brief convert 32-bit CAN frame to little endian
*  @param[in] inFrame data to swap
*
*  if raw CAN data is presented as big endian, convert to little endian
*  before calling getSpeed, getVoltage, getMileage, isSideStand,...
*/

uint64_t convertCanFrameToLittleEndian32(uint64_t inFrame);

/* @brief swap 2 bytes of 16-bit data
*  @param[in] inData data to swap
*
*  If 16-bit data is defined as big endian, it will be
*  swapped of first and second byte.
*/

uint64_t swapForBigEndian16(uint64_t inData);

/* @brief get speed (km/h) from CAN frame
*  @param[in] inFrame data frame
*/

} // namespace

#endif  // _SDL_UTILS_CAN_UTILS_H_