#pragma once

#include "UdsQuery.h"

#define COOL_TEMP_PID 0x05u

using UdsEngineCoolantTemperatureQueryCallback = std::function<void(int16_t)>;

class UdsEngineCoolantTemperatureQuery : public UdsQuery
{
public:
    UdsEngineCoolantTemperatureQuery(const UdsEngineCoolantTemperatureQueryCallback callback,
                                     const uint32_t interval = 0u) : UdsQuery(COOL_TEMP_PID, interval),
                                                                     callback(callback) {}

    void responseReceived(const std::vector<uint8_t> &data) override
    {
        if (callback)
        {
            const uds_frame_s *const uds_frame = (const uds_frame_s *)data.data();
            const int16_t temperature = (int16_t)uds_frame->data[0u] - 40;
            callback(temperature);
        }
    }

private:
    const UdsEngineCoolantTemperatureQueryCallback callback;
};