#pragma once

#include "UdsQuery.h"

#define DIST_TRAV_WITH_MALF_LAMP 0x21u

using UdsDistanceTraveledWithMalfLampCallback = std::function<void(uint8_t)>;

class UdsDistanceTraveledWithMalfLamp : public UdsQuery
{
public:
    UdsDistanceTraveledWithMalfLamp(const UdsDistanceTraveledWithMalfLampCallback callback,
                                    const uint32_t interval = 0u) : UdsQuery(DIST_TRAV_WITH_MALF_LAMP, interval),
                                                                    callback(callback) {}

    void responseReceived(const std::vector<uint8_t> &data) override
    {
        if (callback)
        {
            const uds_frame_s *const uds_frame = (const uds_frame_s *)data.data();
            const uint16_t distance = uds_frame->data[0u] << 8 | uds_frame->data[1u];
            callback(distance);
        }
    }

private:
    const UdsDistanceTraveledWithMalfLampCallback callback;
};