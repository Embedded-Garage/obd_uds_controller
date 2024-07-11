#pragma once

#include "UdsQuery.h"

#define VEHICLE_SPEED_PID 0x0Du

using UdsVehicleSpeedQueryCallback = std::function<void(const uint8_t)>;

class UdsVehicleSpeedQuery : public UdsQuery
{
public:
    UdsVehicleSpeedQuery(const UdsVehicleSpeedQueryCallback callback,
                         const uint32_t interval = 0u) : UdsQuery(VEHICLE_SPEED_PID, interval),
                                                         callback(callback) {}

    void responseReceived(const uint8_t *const data, const uint8_t len) override
    {
        if (len != 8)
        {
            return;
        }
        if (callback)
        {
            const uds_frame_s *const uds_frame = (const uds_frame_s *)data;
            const uint8_t speed = uds_frame->data[0u];
            callback(speed);
        }
    }

private:
    const UdsVehicleSpeedQueryCallback callback;
};