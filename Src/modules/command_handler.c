//
// Created by Ethan Fischer on 10/28/26.
//

#include "modules/command_handler.h"

uint32_t len;


void command_init(const command_t *table, const uint32_t table_len) {
    cmd_table = table;
    cmd_count = table_len;
}

uint8_t process_command(void) {
    for (uint32_t i = 0; i < cmd_count; i++) {
        if (str_equal(command_buffer, cmd_table[i].name)) {
            cmd_table[i].execute();
            len = 0;
            return CMD_SUCCESS;
        }
    }
    len = 0;
    return UNKNOWN_CMD;
}

void append_char_to_command_str(char str) {
    if (len < LINE_MAX - 1U) {
        command_buffer[len++] = str;
        command_buffer[len] = '\0';
    }
}

void remove_char_from_command_str() {
    if (len > 0) {
        len--;
        command_buffer[len] = '\0';
    }
}

static bool str_equal(const char* str1, const char* str2) {

    while (*str1 != '\0' && *str1 == *str2) {
        str1++;
        str2++;
    }

    return *str1 == *str2;
}