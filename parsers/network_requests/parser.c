/**
 * This file is copyrighted by Meandering LLC 2023
 */

#include <stdio.h>
#include "parser.h"

Instruction parse_message(char* buffer)
{
    char command[20] = { 0 };
    int arg1, arg2;

    //should write my own parsing...
    sscanf(buffer, "%s %d %d", command, &arg1, &arg2);

    Command cmd = ERROR;

    if(command[0] == 'P') {
        cmd = PUT;
    } else if(command[0] == 'D') {
        cmd = DELETE;
    } else if (command[0] == 'G') {
        cmd = GET;
    } else if (command[0] == 'S') {
        cmd = SCAN;
    } else if (command[0] == 'F') {
        cmd = FLUSH;
    } else if (command[0] == 'C') {
        cmd = COMPACT;
    } else if (command[0] == 'E') {
        cmd = EXIT;
    } else {
        cmd = ERROR;
    }

    Instruction ins = (Instruction){.cmd=cmd, .arg1=arg1, .arg2=arg2};
    return ins;
}