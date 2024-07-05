#pragma once

#include "UdsQuery.h"

using UdsFuelTankLevelCallback = std::function<void(float)>;

class UdsFuelTankLevelQuery : public UdsQuery
{
public:
    UdsFuelTankLevelQuery(const UdsFuelTankLevelCallback callback, const uint32_t interval = 0u);

    void responseReceived(const twai_message_t &msg) override;

private:
    const UdsFuelTankLevelCallback callback;
};