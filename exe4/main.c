#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int LED_RED = 4;
const int LED_GREEN = 6;
const int BTN_PIN_R = 28;
const int BTN_PIN_G = 26;

volatile int red_flag = 0;
volatile int green_flag = 0;

void btn_callback(uint gpio, uint32_t events) {
  if (gpio == BTN_PIN_R && events == GPIO_IRQ_EDGE_FALL)
    red_flag = 1;
  if (gpio == BTN_PIN_G && events == GPIO_IRQ_EDGE_RISE)
    green_flag = 1;
}

int main() {
  stdio_init_all();
  gpio_init(LED_RED);
  gpio_set_dir(LED_RED, GPIO_OUT);
  gpio_init(LED_GREEN);
  gpio_set_dir(LED_GREEN, GPIO_OUT);
  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);
  gpio_init(BTN_PIN_G);
  gpio_set_dir(BTN_PIN_G, GPIO_IN);
  gpio_pull_up(BTN_PIN_G);
  gpio_set_irq_enabled_with_callback(BTN_PIN_R, GPIO_IRQ_EDGE_FALL, true, btn_callback);
  gpio_set_irq_enabled(BTN_PIN_G, GPIO_IRQ_EDGE_RISE, true);
  while (true) {
    if (red_flag) {
      int state = gpio_get(LED_RED);
      gpio_put(LED_RED, !state);
      red_flag = 0;
    }
    if (green_flag) {
      int state = gpio_get(LED_GREEN);
      gpio_put(LED_GREEN, !state);
      green_flag = 0;
    }
  }
  return 0;
}
