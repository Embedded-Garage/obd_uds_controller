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

    void responseReceived(const std::vector<uint8_t> &data) override {}

private:
    const UdsEngineSpeedQueryCallback callback;
};
