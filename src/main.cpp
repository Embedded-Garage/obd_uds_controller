#include <Arduino.h>
#include "UdsQueryManager.h"
#include "UdsFuelTankLevelQuery.h"

#include "config.h"

#include <memory>

UdsQueryManager udsQueryManager;

void setup()
{
  Serial.begin(115200);
  Serial.println("Hello Embedded Garage!");

  pinMode(PIN_5V_EN, OUTPUT);
  digitalWrite(PIN_5V_EN, HIGH);

  pinMode(CAN_SE_PIN, OUTPUT);
  digitalWrite(CAN_SE_PIN, LOW);
  Serial.println("CAN TRx powered on");

  twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT(GPIO_NUM_27, GPIO_NUM_26, TWAI_MODE_NORMAL);
  twai_timing_config_t t_config = TWAI_TIMING_CONFIG_500KBITS();
  twai_filter_config_t f_config = {.acceptance_code = 0x00000000, .acceptance_mask = 0xFFFFFFFF, .single_filter = true};

  // Install TWAI driver
  if (twai_driver_install(&g_config, &t_config, &f_config) == ESP_OK)
  {
    printf("Driver installed\n");
  }
  else
  {
    printf("Failed to install driver\n");
    return;
  }
  // Start TWAI driver
  if (twai_start() == ESP_OK)
  {
    printf("Driver started\n");
  }
  else
  {
    printf("Failed to start driver\n");
    return;
  }

  auto uptr = std::make_unique<UdsFuelTankLevelQuery>([](float value)
                                  { Serial.printf("Fuel: %.1f\r\n", value); }, 1500);

  udsQueryManager.addQuery(std::move(uptr));
  Serial.println("fuelQuery added to udsQueryManager");
}

void loop()
{
  udsQueryManager.loop(millis());
  delay(1);
}
