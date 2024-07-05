#pragma once

#include <stdint.h>
#include <functional>
#include <driver/twai.h>

#include <Arduino.h>

#pragma pack(push, 1)
using uds_frame_s = struct
{
    uint8_t length;
    uint8_t service;
    uint8_t pid;
    uint8_t data[5u];
};
#pragma pack(pop)

#define UDS_SERVICE_CURR_DATA 1u

class UdsQuery
{
public:
    UdsQuery(const uint8_t pid, const uint32_t interval = 0u);

    twai_message_t buildQuery();

    uint32_t getInterval();

    uint32_t getTimestamp();
    void setTimestamp(const uint32_t new_timestamp);

    void setLastResponseTime(const uint32_t response_time);
    uint32_t getLastResponseTime();

    uint8_t getPid();

    // todo virtual
    // todo zdecydowac gdzie rozkodowywac/kodowac twai_msg do uds_frame
    virtual void responseReceived(const twai_message_t &msg) = 0;

private:
    const uint32_t interval;
    uint32_t timestamp;
    uint32_t last_response_time;
    const uint8_t pid;
};