#pragma once

#include "UdsQuery.h"

#define VEHICLE_SPEED_PID 0x05u

using UdsVehicleSpeedQueryCallback = std::function<void(uint8_t)>;

class UdsVehicleSpeedQuery : public UdsQuery
{
public:
    UdsVehicleSpeedQuery(const UdsVehicleSpeedQueryCallback callback,
                         const uint32_t interval = 0u) : UdsQuery(VEHICLE_SPEED_PID, interval),
                                                         callback(callback) {}

    void responseReceived(const std::vector<uint8_t> &data) override
    {
        if (callback)
        {
            const uds_frame_s *const uds_frame = (const uds_frame_s *)data.data();
            const uint8_t speed = uds_frame->data[0u];
            callback(speed);
        }
    }

private:
    const UdsVehicleSpeedQueryCallback callback;
};