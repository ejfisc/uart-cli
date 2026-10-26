//
// Created by Ethan Fischer on 10/26/26.
//

#include "modules/unit_tests.h"

void print_fw_version(void) {
    log_print(LOG_TESTS, LOG_LVL_INFO, "1.2.0");
}

void led_on(void) {
    GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_HIGH);
}

void led_off(void) {
    GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_LOW);
}