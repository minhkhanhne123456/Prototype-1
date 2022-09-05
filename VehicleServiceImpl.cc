#include <utility>
#include "json/json.h"
#include "json_rc_constants.h"
#include "jsoncpp_reader_wrapper.h"
#include "VehicleServiceImpl.h"
#include "CoreTypes.h"
#include "Log.h"

namespace sdl {

// TODO: Change to member variable when we have configure file
utils::canConfigure VehicleServiceImpl::mCanConfigSpeedMode = {0x610, 8, 0, 3, 1, 0, false}; // SpeedModeStatus
utils::canConfigure VehicleServiceImpl::mCanConfigBrake = {0x610, 8, 11, 1, 1, 0, false}; // BrakeStatus
utils::canConfigure VehicleServiceImpl::mCanConfigBrakeFault = {0x610, 8, 27, 1, 1, 0, false}; // BrakeFaultStatus
utils::canConfigure VehicleServiceImpl::mCanConfigPositionSensorFault = {0x610, 8, 33, 1, 1, 0, false}; // PositionSensorFault
utils::canConfigure VehicleServiceImpl::mCanConfigDriveMode = {0x610, 8, 48, 3, 1, 0, false}; // DriveModeStatus
utils::canConfigure VehicleServiceImpl::mCanConfigSpeedData = {0x611, 7, 0, 16, 10, 0, false}; //SpeedData
utils::canConfigure VehicleServiceImpl::mCanConfigMCUDCVoltage = {0x611, 7, 16, 16, 0.0078125, 0, false}; //MCUDCVoltage
utils::canConfigure VehicleServiceImpl::mCanConfigTotalOdometerMileage = {0x612, 6, 16, 32, 0.1, 0, false}; //TotalOdometerMileage
utils::canConfigure VehicleServiceImpl::mCanConfigThrottlePercentage = {0x631, 8, 16, 16, 1, 0, false}; //ThrottlePercentage
utils::canConfigure VehicleServiceImpl::mCanConfigSideStand = {0x633, 8, 48, 1, 1, 0, false}; //Side_Stand_Status
utils::canConfigure VehicleServiceImpl::mCanConfigSOCDisplay = {0x633, 8, 32, 8, 1, 0, false}; //SOC_Display


VehicleServiceImpl::VehicleServiceImpl()
    : mCallback(nullptr)
    , mId(VEHICLE_SERVICE_ID)
    , mSocketCan() {}

void VehicleServiceImpl::registerCallbacks(VehicleServiceCallbacks* callback) {
    mCallback = callback;
}

void VehicleServiceImpl::setConfigItem(const std::string& inKey, const std::string& inValue) {
    mConfig.set(inKey, inValue);
}

void VehicleServiceImpl::init() {
    ConnectionManager::instance().registerService(this);
    // Load configurations
    if (mConfig.resultConfig()) {
        (void) mSocketCan.startSocketCan(mConfig.mCanInterface, mConfig.mReadTimeoutMs);
    }
}

void VehicleServiceImpl::shutdown() {
    (void) mSocketCan.stopSocketCan();
    if (ConnectionManager::instance().running()) {
        ConnectionManager::instance().shutdown();
    }
}

void VehicleServiceImpl::handleMessage(const Json::Value& message) {
    if (isNotification(message)) {
        processNotification(message);
    } else if (isResponse(message)) {
        processResponse(message);
    } else {
        processRequest(message);
    }
}

uint32_t VehicleServiceImpl::id() const {
    return mId;
}

bool VehicleServiceImpl::isNotification(const Json::Value& message) {
    bool ret = false;
    if (false == message.isMember("id")) {
        ret = true;
    }
    return ret;
}

bool VehicleServiceImpl::isResponse(const Json::Value& message) {
    bool ret = false;
    if ((true == message.isMember("result")) || (true == message.isMember("error"))) {
        ret = true;
    }
    return ret;
}

void VehicleServiceImpl::processNotification(const Json::Value& message) {
    Json::StreamWriterBuilder builder;
    const std::string str_msg = Json::writeString(builder, message) + '\n';
    std::string method = message[json_keys::kMethod].asString();
    LOGD("VehicleServiceImpl::%s() \n%s", __func__, str_msg.c_str());
}

void VehicleServiceImpl::processResponse(const Json::Value& message) {
    //Handled in BasicCummunication.cc
}

void VehicleServiceImpl::processRequest(const Json::Value& message) {
    Json::StreamWriterBuilder builder;
    const std::string str_msg = Json::writeString(builder, message) + '\n';
    std::string id = message[json_keys::kId].asString();
    std::string method = message[json_keys::kMethod].asString();
    LOGD("VehicleServiceImpl::%s()\n%s", __func__, str_msg.c_str());

    Json::Value response;
    response[json_keys::kId] = message[json_keys::kId].asInt();
    response[json_keys::kJsonrpc] = "2.0";
    response[json_keys::kResult][json_keys::kMethod] = method;
    response[json_keys::kResult]["code"] = 0;
    bool isReply = true;

    if (method == "Vehicle.IsReady") {
        response[json_keys::kResult]["available"] = true;
    }

    if (isReply) ConnectionManager::instance().sendJsonMessage(response);
}

double VehicleServiceImpl::getValueFromCan(utils::canConfigure inCanConfig) {
    CanFrame frame;
    double value = 0;
    if (0 != mSocketCan.getCanFrame(inCanConfig.canId, frame)) {
        uint64_t inFrame = convertCanFrameToUint64(frame.data, frame.len);
        if (0 == utils::getCanValue(inCanConfig, inFrame, value)) {
            LOGE("VehicleServiceImpl::%s() cannot get can value, not yet support\n", __func__);
            value = 0;
        }
    } else {
        LOGE("VehicleServiceImpl::%s() cannot get can frame id 0x%x from socket\n", __func__, inCanConfig.canId);
    }
    return value;
}

// TODO: Change to member variable when we have configure file
const Json::Value VehicleServiceImpl::getVehicleData(const Json::Value& root) {
    Json::Value response;
    response[json_keys::kJsonrpc] = "2.0";
    response[json_keys::kResult]["code"] = 0;

    if (root.isMember("params")) {
        const Json::Value& params = root["params"];
        CanFrame frame;
        // get speedData
        if (params.isMember("speedData") && params["speedData"].asBool()) { //[-327680|327670]
            if (getValueFromCan(mCanConfigDriveMode) == 0){//normal
                if (getValueFromCan(mCanConfigSpeedData) >= 327670){
                    response[json_keys::kResult]["speedData"] = 327670;          
                }else {
                    response[json_keys::kResult]["speedData"] = getValueFromCan(mCanConfigSpeedData);          
                }
            }else { //reverse
                if (getValueFromCan(mCanConfigSpeedData) >= 327680){
                    response[json_keys::kResult]["speedData"] = -327680;                              
                }else {
                    response[json_keys::kResult]["speedData"] = - getValueFromCan(mCanConfigSpeedData);          
                }
            }
        } // get MCUDCVoltage
        if (params.isMember("MCUDCVoltage") && params["MCUDCVoltage"].asBool()) { //[0|511.992]
            response[json_keys::kResult]["MCUDCVoltage"] = getValueFromCan(mCanConfigMCUDCVoltage);
        }//get sideStand
        if (params.isMember("sideStand") && params["sideStand"].asBool()) { //[0|1]
            if (getValueFromCan(mCanConfigSideStand) == 0){
                response[json_keys::kResult]["sideStand"] = "Side stand up";
            } else {
                response[json_keys::kResult]["sideStand"] = "Side stand down";
            }
        } //get Soc display
        if (params.isMember("SOCDisplay") && params["SOCDisplay"].asBool()){
            response[json_keys::kResult]["SOCDisplay"] = getValueFromCan(mCanConfigSOCDisplay);
        }
        // get brake status
        if (params.isMember("brake") && params["brake"].asBool()) { //[0|1]
            if (getValueFromCan(mCanConfigBrake) == 0){
                response[json_keys::kResult]["brake"] = "Inactive";
            } else {
                response[json_keys::kResult]["brake"] = "Active";
            }
        } // git speedModeStatus
        if (params.isMember("speedModeStatus") && params["speedModeStatus"].asBool()) { //[0|7]
            if (getValueFromCan(mCanConfigSpeedMode) == 0){
                response[json_keys::kResult]["speedModeStatus"] = "Neutral";
            } else if (getValueFromCan(mCanConfigSpeedMode) == 1){
                response[json_keys::kResult]["speedModeStatus"] = "Mode 1(low speed mode) status";
            } else if (getValueFromCan(mCanConfigSpeedMode) == 2){
                response[json_keys::kResult]["speedModeStatus"] = "Mode 2(middle speed mode) status"; 
            } else if (getValueFromCan(mCanConfigSpeedMode) == 3){
                response[json_keys::kResult]["speedModeStatus"] = "Mode 3(high speed mode) status";
            } else if (getValueFromCan(mCanConfigSpeedMode) == 4){
                response[json_keys::kResult]["speedModeStatus"] = "Invalid";
            }
        } // get totalOdometerMileage
        if (params.isMember("totalOdometerMileage") && params["totalOdometerMileage"].asBool()) { //[0|429497000]
            response[json_keys::kResult]["totalOdometerMileage"] = getValueFromCan(mCanConfigTotalOdometerMileage);
        } // get throttlePercentage
        if (params.isMember("throttlePercentage") && params["throttlePercentage"].asBool()) { //[0|100]
            if (getValueFromCan(mCanConfigThrottlePercentage) >= 100){
                response[json_keys::kResult]["throttlePercentage"] = 100;
            } else {
                    response[json_keys::kResult]["throttlePercentage"] = getValueFromCan(mCanConfigThrottlePercentage);
            }
        } // get brakeFault
        if (params.isMember("brakeFault") && params["brakeFault"].asBool()) { //[0|1]
            if (getValueFromCan(mCanConfigBrakeFault) == 0){
                response[json_keys::kResult]["brakeFault"] = "No Fault";
            } else {
                response[json_keys::kResult]["brakeFault"] = "Fault";
            }
        } // get positionSensorFault
        if (params.isMember("positionSensorFault") && params["positionSensorFault"].asBool()) { //[0|1]
            if (getValueFromCan(mCanConfigPositionSensorFault) == 0){
                response[json_keys::kResult]["positionSensorFault"] = "No Fault";
            } else {
                response[json_keys::kResult]["positionSensorFault"] = "Fault";
            }
        } // get driveMode
        if (params.isMember("driveMode") && params["driveMode"].asBool()) { //[0|7]
            if (getValueFromCan(mCanConfigDriveMode) == 0){
                response[json_keys::kResult]["driveMode"] = "NormalMode Status";
            }else {
                response[json_keys::kResult]["driveMode"] = "Reverse Mode status";               
            }
        }  
    } else {
        response[json_keys::kResult]["code"] = -1;
        response[json_keys::kResult]["message"] = "Request has no param";
    }
    return response;
}

int VehicleServiceImpl::subscribeVehicleData(const Json::Value& params) {
    // TODO: do nothing
    return 0;
}

int VehicleServiceImpl::unsubscribeVehicleData(const Json::Value& params) {
    // TODO: do nothing
    return 0;
}

}
