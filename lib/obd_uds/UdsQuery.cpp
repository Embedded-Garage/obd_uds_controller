#include "UdsQuery.h"

#include <driver/twai.h>
#include <string.h>

UdsQuery::UdsQuery(const uint8_t pid, const uint32_t interval) : pid(pid),
                                                                 interval(interval)
{
}

twai_message_t UdsQuery::buildQuery()
{
    twai_message_t msg =
        {
            .flags = 0u,
            .identifier = 0x7DFu,
            .data_length_code = 8u,
        };
    msg.extd = 0u;

    uds_frame_s *uds_frame = (uds_frame_s *)msg.data;
    uds_frame->add_bytes = 0x02u;
    uds_frame->pid = pid;
    uds_frame->service = UDS_SERVICE_CURR_DATA;
    memset(uds_frame->data, 0xAA, sizeof(uds_frame->data));

    return msg;
}

uint32_t UdsQuery::getInterval()
{
    return interval;
}

uint32_t UdsQuery::getTimestamp()
{
    return timestamp;
}

void UdsQuery::setTimestamp(const uint32_t new_timestamp)
{
    timestamp = new_timestamp;
}

void UdsQuery::setLastResponseTime(const uint32_t response_time)
{
    last_response_time = response_time;
}

uint32_t UdsQuery::getLastResponseTime()
{
    return last_response_time;
}

uint8_t UdsQuery::getPid()
{
    return pid;
}
