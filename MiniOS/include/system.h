
#ifndef	SYSTEM_H
#define	SYSTEM_H

#include "types.h"
#include "config.h"

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
	uint8_t priorityFlag;

	/*sytem mode*/
	uint8_t sysMode;

	/*system running flag*/
	uint8_t sysRunningFlag;	
};

/*task control block*/
struct TCB {
	/*task delay time, unit: jiffies*/
	uint16_t delayTime;

	/*task stack pointer*/
	uint8_t taskSP;
	
	/*current task status*/
	uint8_t curTskStat;

	/*store task status*/
	uint8_t storeTskStat;
};


/*system control block variable*/
extern struct SCB gSCB;



/*task stacks*/
extern uint8_t idata gTskStacks[MAX_TSK_NUM][MAX_TSK_STACK_SIZE];

/*task queue*/
extern uint8_t idata gTskQueue[MAX_TSK_NUM];
extern uint8_t idata gPriorTskQueue[MAX_TSK_NUM];

/*task TCBs*/
extern struct TCB idata gTCBs[MAX_TSK_NUM];

/*tasks declaration*/
void Task0();
void Task1();
void Task2();
void Task3();
void Task4();

#endif
