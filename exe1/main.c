#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include <stdbool.h>

const int BTN_PIN_R = 28;

volatile bool fall_flag = false;
volatile bool rise_flag = false;


void btn_callback(uint gpio, uint32_t events) {
    if (events & GPIO_IRQ_EDGE_FALL) { 
        fall_flag = true;
    }
    if (events & GPIO_IRQ_EDGE_RISE) { 
        rise_flag = true;
    }
}

int main() {
    stdio_init_all();

    gpio_init(BTN_PIN_R);
    gpio_set_dir(BTN_PIN_R, GPIO_IN);
    gpio_pull_up(BTN_PIN_R);

    gpio_set_irq_enabled_with_callback(
        BTN_PIN_R, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &btn_callback);

    while (true) {
        if (fall_flag) {
            printf("fall \n");
            fall_flag = false;
        }
        if (rise_flag) {
            printf("rise \n");
            rise_flag = false;
        }
    }
    return 0;
}
