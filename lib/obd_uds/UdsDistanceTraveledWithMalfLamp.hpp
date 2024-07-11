#pragma once

#include "UdsQuery.h"

#define DIST_TRAV_WITH_MALF_LAMP 0x21u

using UdsDistanceTraveledWithMalfLampCallback = std::function<void(const uint8_t)>;

class UdsDistanceTraveledWithMalfLamp : public UdsQuery
{
public:
    UdsDistanceTraveledWithMalfLamp(const UdsDistanceTraveledWithMalfLampCallback callback,
                                    const uint32_t interval = 0u) : UdsQuery(DIST_TRAV_WITH_MALF_LAMP, interval),
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
            const uint16_t distance = uds_frame->data[0u] << 8 | uds_frame->data[1u];
            callback(distance);
        }
    }

private:
    const UdsDistanceTraveledWithMalfLampCallback callback;
};