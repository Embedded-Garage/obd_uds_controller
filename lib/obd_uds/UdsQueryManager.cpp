#include "UdsQueryManager.h"

#include "driver/twai.h"
#include <Arduino.h>
#include <vector>

void UdsQueryManager::loop(const uint32_t time_ms)
{
    checkRx(time_ms);
    checkTx(time_ms);
}

void UdsQueryManager::addQuery(std::unique_ptr<UdsQuery> &&query)
{
    queries.push_back(std::move(query));
}

void UdsQueryManager::checkRx(const uint32_t time_ms)
{
    twai_message_t rx_msg;

    while (ESP_OK == twai_receive(&rx_msg, 0))
    {
        if (8u == rx_msg.data_length_code)
        {
            const uds_frame_s *const uds_frame = (const uds_frame_s *)rx_msg.data;

            for (auto &query_uptr : queries)
            {
                auto *query = query_uptr.get();
                if (query->getPid() == uds_frame->pid)
                {
                    auto data = std::vector<uint8_t>(std::begin(rx_msg.data), std::end(rx_msg.data));
                    query->responseReceived(data);

                    /* calculate response time */
                    const uint32_t time_from_last_shoot = time_ms - query->getTimestamp();
                    query->setLastResponseTime(time_from_last_shoot);
                }
            }
        }
    }
}

void UdsQueryManager::checkTx(const uint32_t time_ms)
{
    twai_message_t tx_msg;

    for (auto &query_uptr : queries)
    {
        auto *query = query_uptr.get();
        const uint32_t time_from_last_shoot = time_ms - query->getTimestamp();
        if (time_from_last_shoot >= query->getInterval())
        {
            tx_msg = query->buildQuery();
            if (ESP_OK == twai_transmit(&tx_msg, 0))
            {
                query->setTimestamp(time_ms);
            }
        }
    }
}
