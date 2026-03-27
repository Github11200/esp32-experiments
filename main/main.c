#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define GPIO_OUT_W1TS_REG 0x3FF44008 // Set register
#define GPIO_OUT_W1TC_REG 0x3FF4400C // Clear register
#define GPIO_ENABLE_REG 0x3FF44020   // Enable a pin
#define GPIO_PIN 23
#define DELAY_MS 2000

void app_main(void)
{
  volatile uint32_t *gpio_out_w1ts_reg = (volatile uint32_t *)GPIO_OUT_W1TS_REG;
  volatile uint32_t *gpio_out_w1tc_reg = (volatile uint32_t *)GPIO_OUT_W1TC_REG;
  volatile uint32_t *gpio_enable_reg = (volatile uint32_t *)GPIO_ENABLE_REG;

  // Enable the pin we will be writing to
  *gpio_enable_reg = (1 << GPIO_PIN);

  while (1)
  {
    *gpio_out_w1ts_reg = (1 << GPIO_PIN);
    vTaskDelay(pdMS_TO_TICKS(DELAY_MS));
    *gpio_out_w1tc_reg = (1 << GPIO_PIN);
    vTaskDelay(pdMS_TO_TICKS(DELAY_MS));
  }
}
