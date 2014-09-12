
#include "../include/system.h"
#include "../include/types.h"

struct SCB gSCB;

uint8_t idata gTskStacks[MAX_TSK_NUM][MAX_TSK_STACK_SIZE];

uint8_t idata gTskQueue[MAX_TSK_NUM];

struct TCB idata gTCBs[MAX_TSK_NUM];
