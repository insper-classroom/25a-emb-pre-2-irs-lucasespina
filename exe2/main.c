#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const uint LED_PIN = 4;
const uint BTN_PIN = 28;

volatile bool button_pressed_flag = false;

void button_callback(uint gpio, uint32_t events) {
    if (events & GPIO_IRQ_EDGE_FALL) {
        button_pressed_flag = true;
    }
}

int main() {
    stdio_init_all();

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_init(BTN_PIN);
    gpio_set_dir(BTN_PIN, GPIO_IN);
    gpio_pull_up(BTN_PIN);

    gpio_set_irq_enabled_with_callback(BTN_PIN, GPIO_IRQ_EDGE_FALL, true, button_callback);

    while (true) {
        if (button_pressed_flag) {
            bool led_state = gpio_get(LED_PIN);
            gpio_put(LED_PIN, !led_state);
            button_pressed_flag = false;
        }
    }
    
    return 0;
}
