#pragma once

#include "UdsQuery.h"

#define FUEL_TANK_LEVEL_PID 0x2Fu

using UdsFuelTankLevelQuerylCallback = std::function<void(float)>;

class UdsFuelTankLevelQuery : public UdsQuery
{
public:
    UdsFuelTankLevelQuery(const UdsFuelTankLevelQuerylCallback callback,
                          const uint32_t interval = 0u)
        : UdsQuery(FUEL_TANK_LEVEL_PID, interval),
          callback(callback) {}

    void responseReceived(const std::vector<uint8_t> &data) override
    {
        if (callback)
        {
            const uds_frame_s *const uds_frame = (const uds_frame_s *)data.data();
            const float fuel = ((float)uds_frame->data[0u] * 100.0f) / 255.0f;
            callback(fuel);
        }
    };

private:
    const UdsFuelTankLevelQuerylCallback callback;
};