#include "UdsQueryManager.h"

#include "driver/twai.h"

#include <Arduino.h>

void UdsQueryManager::loop(const uint32_t time_ms)
{
    checkRx(time_ms);
    checkTx(time_ms);
}

void UdsQueryManager::addQuery(const UdsQuery &query)
{
    queries.push_back(query);
}

void UdsQueryManager::checkRx(const uint32_t time_ms)
{
    twai_message_t rx_msg;

    while (ESP_OK == twai_receive(&rx_msg, 0))
    {
        if (8u == rx_msg.data_length_code)
        {
            const uds_frame_s *const uds_frame = (const uds_frame_s *)rx_msg.data;

            for (auto &query : queries)
            {
                if (query.getPid() == uds_frame->pid)
                {
                    Serial.println("resp rcvd");
                    query.responseReceived(rx_msg);

                    /* calculate response time */
                    const uint32_t time_from_last_shoot = time_ms - query.getTimestamp();
                    query.setLastResponseTime(time_from_last_shoot);
                }
            }
        }
    }
}

void UdsQueryManager::checkTx(const uint32_t time_ms)
{
    twai_message_t tx_msg;

    for (auto &query : queries)
    {
        const uint32_t time_from_last_shoot = time_ms - query.getTimestamp();
        if (time_from_last_shoot >= query.getInterval())
        {
            tx_msg = query.buildQuery();
            if (ESP_OK == twai_transmit(&tx_msg, 0))
            {
                query.setTimestamp(time_ms);
            }
        }
    }
}
