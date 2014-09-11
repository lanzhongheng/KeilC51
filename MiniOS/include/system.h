
#ifndef	SYSTEM_H
#define	SYSTEM_H

#include "types.h"

/*system control block*/
struct SCB {
	/*task number*/
	uint8_t curTskNum;
	uint8_t nextTskNum;	

	/*time slice, unit: jiffies*/
	uint8_t timeSlice;	

	/*schedule mutex*/
	uint8_t schMutex;

	/*interrupt nesting counter*/
	uint8_t intNestCnt;

	/*preemptive task flag*/
	uint8_t eventFlag;

	/*sytem mode*/
	uint8_t sysMode;

	/*system running flag*/
	uint8_t sysRunningFlag;	
};

/*task control block*/
struct TCB {
	/*task time slice, unit: jiffies*/
	uint16_t timeSlice;

	/*task stack pointer*/
	uint8_t taskSP;
	
	/*current task status*/
	uint8_t curTskStat;

	/*store task status*/
	uint8_t storeTskStat;
};


/*system control block variable*/
struct SCB gSCB;

/*maximum task number*/
//#ifndef MAX_TSK_NUM
#define	MAX_TSK_NUM		5
//#endif

/*maximum task stack size*/
//#ifndef MAX_TSK_STACK_SIZE
#define	MAX_TSK_STACK_SIZE	20
//#endif

/*task stacks*/
uint8_t idata gTskStacks[MAX_TSK_NUM][MAX_TSK_STACK_SIZE];

/*task queue*/
uint8_t idata gTskQueue[MAX_TSK_NUM];

/*task TCBs*/
struct TCB idata gTCBs[MAX_TSK_NUM];

#endif
