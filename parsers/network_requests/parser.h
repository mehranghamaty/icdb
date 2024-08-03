/**
 * This file is copyrighted by Meandering LLC 2023
 */

#ifndef LSM_PARSER_H
#define LSM_PARSER_H

typedef enum Command {PUT, DELETE, GET, SCAN, FLUSH, COMPACT, ERROR, EXIT} Command;

typedef struct Instruction
{
    Command cmd;
    int arg1;
    int arg2;
} Instruction;

Instruction parse_message(char* buffer);

#endif //LSM_PARSER_H
