//
// Created by Ethan Fischer on 10/28/26.
//

#include "modules/terminal_interface.h"

void terminal_init(void) {
    terminal_clear();
    usart2_write_buf((uint8_t*)"STM32 > ", 8);
}

void terminal_update_newline() {
    usart2_write_buf((uint8_t*)"STM32 > ", 8);
}

void terminal_update_cursor(const uint8_t key) {
    usart2_write(key);
}

void terminal_backspace(void) {
    usart2_write((uint8_t)'\b');
    usart2_write((uint8_t)' ');
    usart2_write((uint8_t)'\b');
}

void terminal_clear(void) {
    usart2_write_buf((uint8_t*)"\033[2J\033[H", 11);
}