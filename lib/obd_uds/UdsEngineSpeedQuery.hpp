#pragma once

#include "UdsQuery.h"

#define ENGINE_SPEED_PID 0x0Cu

using UdsEngineSpeedQueryCallback = std::function<void(float)>;

class UdsEngineSpeedQuery : public UdsQuery
{
public:
    UdsEngineSpeedQuery(const UdsEngineSpeedQueryCallback callback,
                        const uint32_t interval = 0u)
        : UdsQuery(ENGINE_SPEED_PID, interval),
          callback(callback) {}

    void responseReceived(const std::vector<uint8_t> &data) override
    {
        if (callback)
        {
            const uds_frame_s *const uds_frame = (const uds_frame_s *)data.data();
            const uint16_t engine_raw = ((uint16_t)uds_frame->data[0u] << 8) | uds_frame->data[0u];
            const float engine = (float)engine_raw / 4.0;
            callback(engine);
        }
    }

private:
    const UdsEngineSpeedQueryCallback callback;
};
