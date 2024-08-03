/**
 * This file is copyrighted by Meandering LLC 2023
 */

#ifndef LSM_HANDLER_H
#define LSM_HANDLER_H

#include "../parsers/network_requests/parser.h"
#include "../datastructures/lsm/lsm.h"

void *server_thread(void *vargp);
void run_instruction(LSMTree* tree, Instruction ins);

#endif //LSM_HANDLER_H
