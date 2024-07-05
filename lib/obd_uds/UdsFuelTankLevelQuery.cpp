#include "UdsFuelTankLevelQuery.h"
#include "UdsQuery.h"

#define FUEL_TANK_LEVEL_PID 0x2Fu

UdsFuelTankLevelQuery::UdsFuelTankLevelQuery(const UdsFuelTankLevelCallback callback, const uint32_t interval) : UdsQuery(FUEL_TANK_LEVEL_PID, interval),
                                                                                                                 callback(callback)

{
    callback(1234.0f);
}

void UdsFuelTankLevelQuery::responseReceived(const twai_message_t &msg)
{
    Serial.println("deriv resp_rcvd");
    if (callback)
    {
        const uds_frame_s *const uds_frame = (uds_frame_s *const)msg.data;
        const float fuel = ((float)uds_frame->data[0u] * 100.0f) / 255.0f;
        callback(fuel);
    }
}
