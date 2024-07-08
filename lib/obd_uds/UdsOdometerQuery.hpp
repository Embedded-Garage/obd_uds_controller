#pragma once

#include "UdsQuery.h"

#define FUEL_TANK_LEVEL_PID 0x2Fu

using UdsOdometerQueryCallback = std::function<void(uint32_t)>;

class UdsOdometerQuery : public UdsQuery
{
public:
    UdsOdometerQuery(const UdsOdometerQueryCallback callback,
                     const uint32_t interval = 0u)
        : UdsQuery(FUEL_TANK_LEVEL_PID, interval),
          callback(callback) {}

    void responseReceived(const std::vector<uint8_t> &data) override
    {
        if (callback)
        {
            const uds_frame_s *const uds_frame = (const uds_frame_s *)data.data();
            const uint32_t odometer = uds_frame->data[0u] << 24 |
                                      uds_frame->data[1u] << 16 |
                                      uds_frame->data[2u] << 8 |
                                      uds_frame->data[3u];
            callback(odometer);
        }
    };

private:
    const UdsOdometerQueryCallback callback;
};