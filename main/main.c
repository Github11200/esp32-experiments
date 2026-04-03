#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h" // For PWM control
#include "driver/gpio.h" // For GPIO control

#define MOTOR_IN1_PIN GPIO_NUM_21    // IN1 pin connected to motor driver
#define MOTOR_IN2_PIN GPIO_NUM_22    // IN2 pin connected to motor driver
#define MOTOR_ENABLE_PIN GPIO_NUM_23 // Enable pin for PWM control

#define MOTOR_PWM_FREQ 5000 // Frequency in Hz for PWM
#define MOTOR_PWM_CHANNEL LEDC_CHANNEL_0
#define MOTOR_PWM_MODE LEDC_HIGH_SPEED_MODE
#define MOTOR_PWM_TIMER LEDC_TIMER_0
#define MOTOR_PWM_RES LEDC_TIMER_10_BIT // PWM resolution (10-bit)
#define MAX_DUTY_CYCLE 1023             // Maximum duty cycle for 10-bit resolution

void app_main(void)
{
  // Configure GPIO for motor direction control
  esp_rom_gpio_pad_select_gpio(MOTOR_IN1_PIN);
  gpio_set_direction(MOTOR_IN1_PIN, GPIO_MODE_OUTPUT);
  esp_rom_gpio_pad_select_gpio(MOTOR_IN2_PIN);
  gpio_set_direction(MOTOR_IN2_PIN, GPIO_MODE_OUTPUT);

  // Configure PWM timer
  ledc_timer_config_t pwm_timer = {
      .speed_mode = MOTOR_PWM_MODE,
      .duty_resolution = MOTOR_PWM_RES,
      .timer_num = MOTOR_PWM_TIMER,
      .freq_hz = MOTOR_PWM_FREQ,
      .clk_cfg = LEDC_AUTO_CLK};
  ledc_timer_config(&pwm_timer);

  // Configure PWM channel
  ledc_channel_config_t pwm_channel = {
      .gpio_num = MOTOR_ENABLE_PIN,
      .speed_mode = MOTOR_PWM_MODE,
      .channel = MOTOR_PWM_CHANNEL,
      .intr_type = LEDC_INTR_DISABLE,
      .timer_sel = MOTOR_PWM_TIMER,
      .duty = 0,
      .hpoint = 0};
  ledc_channel_config(&pwm_channel);

  int duty_cycle = 700;
  int direction = 1; // 1 for clockwise, 0 for anticlockwise

  while (true)
  {
    // // Set motor direction
    // if (direction == 1)
    // {
    //   gpio_set_level(MOTOR_IN1_PIN, 1);
    //   gpio_set_level(MOTOR_IN2_PIN, 0);
    //   printf("Direction: Clockwise\n");
    // }
    // else
    // {
    //   gpio_set_level(MOTOR_IN1_PIN, 0);
    //   gpio_set_level(MOTOR_IN2_PIN, 1);
    //   printf("Direction: Anticlockwise\n");
    // }

    // // Set PWM duty cycle to control speed
    // ledc_set_duty(MOTOR_PWM_MODE, MOTOR_PWM_CHANNEL, duty_cycle);
    // ledc_update_duty(MOTOR_PWM_MODE, MOTOR_PWM_CHANNEL);

    // // Increase the duty cycle for speed control
    // duty_cycle += 10; // Increase speed gradually
    // printf("Duty Cycle: %d\n", duty_cycle);

    // if (duty_cycle > MAX_DUTY_CYCLE)
    // {
    //   // Briefly disable motor between direction changes
    //   gpio_set_level(MOTOR_IN1_PIN, 0);
    //   gpio_set_level(MOTOR_IN2_PIN, 0);
    //   vTaskDelay(pdMS_TO_TICKS(100)); // Short delay to stop

    //   // Reset duty cycle and toggle direction
    //   duty_cycle = 700;
    //   direction = !direction;
    //   printf("Toggling direction\n");
    // }

    // vTaskDelay(pdMS_TO_TICKS(200)); // Delay for observation
  }
}
