#pragma once

#include "UdsQuery.h"

#define ODOMETER_ID 0xA6u

using UdsOdometerQueryCallback = std::function<void(const uint32_t)>;

class UdsOdometerQuery : public UdsQuery
{
public:
    UdsOdometerQuery(const UdsOdometerQueryCallback callback,
                     const uint32_t interval = 0u)
        : UdsQuery(ODOMETER_ID, interval),
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