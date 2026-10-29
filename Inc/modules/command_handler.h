//
// Created by Ethan Fischer on 10/28/26.
//

#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <stdint.h>
#include <stdbool.h>
#include "device_drivers/usart2.h"

#define LINE_MAX 32U

typedef struct {
    char const *name;
    void (*execute)(void);
    char const *help_text;
} command_t;

static char command_buffer[LINE_MAX];
static uint32_t cmd_count;
static const command_t *cmd_table;

void command_init(const command_t *table, uint32_t table_len);

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

static bool str_equal(const char* str1, const char* str2);

#endif //COMMAND_HANDLER_H
