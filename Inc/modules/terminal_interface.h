//
// Created by Ethan Fischer on 10/28/26.
//

#ifndef TERMINAL_INTERFACE_H
#define TERMINAL_INTERFACE_H

#include "device_drivers/usart2.h"
#include "modules/command_handler.h"

void terminal_init(void);
void terminal_update_newline(void);
void terminal_update_cursor(uint8_t key);
void terminal_backspace(void);

#endif //TERMINAL_INTERFACE_H
