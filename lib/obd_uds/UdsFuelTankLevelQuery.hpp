#pragma once

#include "UdsQuery.h"

#define FUEL_TANK_LEVEL_PID 0x2Fu

using UdsFuelTankLevelQuerylCallback = std::function<void(const float)>;

class UdsFuelTankLevelQuery : public UdsQuery
{
public:
    UdsFuelTankLevelQuery(const UdsFuelTankLevelQuerylCallback callback,
                          const uint32_t interval = 0u)
        : UdsQuery(FUEL_TANK_LEVEL_PID, interval),
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
            const float fuel = ((float)uds_frame->data[0u] * 100.0f) / 255.0f;
            callback(fuel);
        }
    };

private:
    const UdsFuelTankLevelQuerylCallback callback;
};