//
// Created by Ethan Fischer on 10/28/26.
//

#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include "modules/unit_tests.h"

static char* command_buffer[16];

typedef struct {
    char const *name;
    void (*execute)(void);
    char const *help_text;
} command_t;

static const command_t commands[] = {
    {.name = "ver", .execute = &print_fw_version, .help_text = "prints the firmware version"},
    {.name = "ledOn", .execute = &led_on, .help_text = "turns led on"},
    {.name = "ledOff", .execute = &led_off, .help_text = "turns led off"},
};

/**
 * processes the command in the buffer
 */
void process_command(void);


/**
 * appends the latest char to the command string buffer
 * @param str char to add to command string buffer
 */
void append_char_to_command_str(char str);

/**
 * removes the latest char from the command string buffer
 */
void remove_char_from_command_str(void);

#endif //COMMAND_HANDLER_H
