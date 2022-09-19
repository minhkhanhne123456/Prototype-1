#include <cstdint>
#include <map>
#include "CanUtils.h"
#include "Log.h"

namespace utils {

// TODO: Change to member variable when we have configure file
// CAN configure for speed value => SpeedData
uint8_t SPEEDDATA_STARTBIT = 0;
uint16_t SPEEDDATA_LENGTH = 16;
const int16_t SPEEDDATA_MASK = 0xFFFF;
const double SPEEDDATA_SCALE = 10;
const double SPEEDDATA_OFFSET = 0;
const bool SPEEDDATA_IS_BIGENDIAN = false;
// CAN configure for voltage value => MCUDCVoltage
uint8_t MCUDCVOLTAGE_STARTBIT = 16;
uint16_t MCUDCVOLTAGE_LENGTH = 16;
const uint16_t MCUDCVOLTAGE_MASK = 0xFFFF;
const double MCUDCVOLTAGE_SCALE = 0.0078125;
const double MCUDCVOLTAGE_OFFSET = 0;
const bool MCUDCVOLTAGE_IS_BIGENDIAN = false;
// CAN configure for mileage value in CAN ID _0x603 => TotalOdometerMileage
uint8_t TOTALODOMERTERMILEAGE_STARTBIT = 16;
uint16_t TOTALODOMERTERMILEAGE_LENGTH = 32;
const uint32_t TOTALODOMERTERMILEAGE_MASK = 0xFFFFFFFF;
const double TOTALODOMERTERMILEAGE_SCALE = 0.1;
const double TOTALODOMERTERMILEAGE_OFFSET = 0;
const bool TOTALODOMERTERMILEAGE_IS_BIGENDIAN = false;
// CAN configure for side stand status => Side_Stand_status
const uint8_t SIDESTAND_STARTBIT = 48;
const uint16_t SIDESTAND_LENGTH = 1;
const uint16_t SIDESTAND_MASK = 0x1;
// CAN configure for brake status => BrakeStatus
const uint8_t BRAKE_STARTBIT = 11;
const uint16_t BRAKE_LENGTH = 1;
const uint16_t BRAKE_MASK = 0x1;
// CAN configure for parking status => SpeedModeStatus
const uint8_t SPEEDMODE_STARTBIT = 0;
const uint16_t SPEEDMODE_LENGTH = 3;
const uint16_t SPEEDMODE_MASK = 0x7;
// Different signals
// CAN configure for DriveModeStatus
const uint8_t DRIVEMODE_STARTBIT = 48;
const uint16_t DRIVEMODE_LENGTH = 3;
const uint16_t DRIVEMODE_MASK = 0x7;
// CAN configure for PositionSensorFault
const uint8_t POSITIONSENSORFAULT_STARTBIT = 33;
const uint16_t POSITIONSENSORFAULT_LENGTH = 1;
const uint16_t POSITIONSENSORFAULT_MASK = 0x1;
// CAN configure for BrakeFaultStatus
const uint8_t BRAKEFAULT_STARTBIT = 27;
const uint16_t BRAKEFAULT_LENGTH = 1;
const uint16_t BRAKEFAULT_MASK = 0x1;
// CAN configure for ACD1 (missing in Klara db) => ThrottlePercentage
uint8_t THROTTLEPERCENTAGE_STARTBIT = 16;
uint16_t THROTTLEPERCENTAGE_LENGTH = 16;
const int16_t THROTTLEPERCENTAGE_MASK = 0xFFFF;
const double THROTTLEPERCENTAGE_SCALE = 1;
const double THROTTLEPERCENTAGE_OFFSET = 0;
const bool THROTTLEPERCENTAGE_IS_BIGENDIAN = false; 
// CAN configure for SOC_Display (new signal)
const uint8_t SOCDISPLAY_STARTBIT = 32;
const uint16_t SOCDISPLAY_LENGTH = 8;
const uint16_t SOCDISPLAY_MASK = 0xFF;

// TODO: Change to member variable when we have configure file
uint8_t lengthToMask(uint32_t inLength, uint32_t& outMask) {
    uint8_t ret = 1;
    if (inLength == 1) {
        outMask = 0x1;
    } else if (inLength == 3) {
        outMask = 0x7;
    } else if (inLength == 8) {
        outMask = 0xff;
    } else if (inLength == 16) {
        outMask = 0xffff;
    } else if (inLength == 32) {
        outMask = 0xffffffff;
    } else {
        // not yet support
        ret = 0;
    }
    return ret;
}

// TODO: Change to member variable when we have configure 
// uint64_t convertCanFrameToLittleEndian(uint64_t inFrame);
//     if 

uint64_t convertCanFrameToLittleEndian64(uint64_t inFrame) {
    return ((((inFrame) >> 56) & 0x00000000000000FF) | (((inFrame) >> 40) & 0x000000000000FF00) |
    (((inFrame) >> 24) & 0x0000000000FF0000) | (((inFrame) >>  8) & 0x00000000FF000000) |
    (((inFrame) <<  8) & 0x000000FF00000000) | (((inFrame) << 24) & 0x0000FF0000000000) |
    (((inFrame) << 40) & 0x00FF000000000000) | (((inFrame) << 56) & 0xFF00000000000000) );
}

uint64_t convertCanFrameToLittleEndian56(uint64_t inFrame) {
    return ((((inFrame) >> 48) & 0x000000000000FF) | (((inFrame) >> 32) & 0x0000000000FF00) |
    (((inFrame) >> 16) & 0x00000000FF0000) | ((inFrame) & 0x000000FF000000) |
    (((inFrame) << 16) & 0x0000FF00000000) | (((inFrame) << 32) & 0x00FF0000000000) |
    (((inFrame) << 48) & 0xFF000000000000) );
}

uint64_t convertCanFrameToLittleEndian48(uint64_t inFrame) {
    return ((((inFrame) >> 40) & 0x0000000000FF) | (((inFrame) >> 24) & 0x00000000FF00) |
    (((inFrame) >> 8) & 0x000000FF0000) | (((inFrame) <<  8) & 0x0000FF000000) | 
    (((inFrame) << 24) & 0x00FF00000000) |(((inFrame) << 40) & 0xFF0000000000));
}


uint64_t convertCanFrameToLittleEndian32(uint64_t inFrame) {
    return ( (((inFrame) >> 24) & 0x000000FF) | (((inFrame) >>  8) & 0x0000FF00) |
    (((inFrame) <<  8) & 0x00FF0000) | (((inFrame) << 24) & 0xFF000000) );
}

uint64_t swapForBigEndian16(uint64_t inData) {
    return (((inData << 8) & 0xff00) | ((inData >> 8) & 0x00ff));
}

uint8_t getCanValue(canConfigure inCanConfig, uint64_t inFrame, double& outValue) {
    uint8_t ret = 1;
    uint64_t cutFrame;
    uint32_t mask;
    // for little endian
    if (inCanConfig.canLength == 8) {
        inFrame = convertCanFrameToLittleEndian64(inFrame);
    } else if (inCanConfig.canLength == 7) {
        inFrame = convertCanFrameToLittleEndian56(inFrame);
    } else if (inCanConfig.canLength == 6) {
        inFrame = convertCanFrameToLittleEndian48(inFrame);
    }else if (inCanConfig.canLength == 4) {
        inFrame = convertCanFrameToLittleEndian32(inFrame);
    } 
    else {
        LOGE("CanUtils %s() can frame length %d bytes not yet support\n", __func__, inCanConfig.canLength);
        ret = 0;
    }
    if (0 == lengthToMask(inCanConfig.length, mask)) {
        LOGE("CanUtils %s() cannot get the value with length %d not yet support\n", __func__, inCanConfig.length);
        ret = 0;
    }
    // for big endian
    if ((inCanConfig.length > 1) && inCanConfig.isBigendian) {
        cutFrame = (inFrame >> (inCanConfig.startBit + 8 - inCanConfig.length)) & mask;
        if (inCanConfig.length == 16) {
        cutFrame = swapForBigEndian16(cutFrame);
        } else {
            LOGE("CanUtils %s() cannot swap for bigendian with length %d not yet support\n", __func__, inCanConfig.length);
            ret = 0;
        }
    } else {
        cutFrame = (inFrame >> inCanConfig.startBit) & mask;
    }
    outValue = cutFrame * inCanConfig.scale + inCanConfig.offset;
    return ret;
}

} // namespace
