
#include "../include/system.h"
#include "../include/macro.h"

void InitVars();
void InitTasks();
void setTaskStack(TaskPtr task, uint8_t taskNum);
void setTCB(uint8_t taskNum);

void InitSystem()
{
	InitVars();
	InitTasks();
}

void InitVars()
{
	uint8_t i;
	uint8_t j;

	/*init SCB*/
	gSCB.curTskNum = 0;
	gSCB.nextTskNum = 0;	
	gSCB.timeSlice = 0;
	gSCB.intNestCnt = 0;
	gSCB.schMutex = 0;	
	gSCB.eventFlag = EVENT_OFF;
	gSCB.sysMode = SYS_STOP;
	gSCB.sysRunningFlag = SYS_OFF;
	
	/*init task queue*/	
	for (i = 0; i < MAX_TSK_NUM; i++)
	{
		gTskQueue[i] = 0;
	}

	/*init task stacks*/
	for (i = 0; i < MAX_TSK_NUM; i++)
	{
		for (j = 0; j < MAX_TSK_STACK_SIZE; j++)
		{
			gTskStacks[i][j] = 0;
		}
	}
}

void InitTasks()
{
	uint8_t i;

	/*push tasks' entries into task stack*/
	setTaskStack(Task0, 0);	
	setTaskStack(Task1, 1);
	setTaskStack(Task2, 2);
	setTaskStack(Task3, 3);
	setTaskStack(Task4, 4);

	/*set TCBs*/
	for (i = 0; i < MAX_TSK_NUM; i++)
	{
		setTCB(i);
	}

	/*add task to task queue, NO.0 task is an idle task*/
	for (i = 0; i < MAX_TSK_NUM; i++)
	{
		gTskQueue[i] = i;
	}
}

void setTaskStack(TaskPtr task, uint8_t taskNum)
{
	gTskStacks[taskNum][0] = (uint8_t)((uint16_t)task & 0xff);
	gTskStacks[taskNum][1] = (uint8_t)(((uint16_t)task >> 8) & 0xff);		
} 

void setTCB(uint8_t taskNum)
{
	gTCBs[taskNum].delayTime = 0;
	gTCBs[taskNum].taskSP = (uint16_t)(& gTskStacks[taskNum][1]) & 0xff;
	gTCBs[taskNum].curTskStat = TSK_READY;
	gTCBs[taskNum].storeTskStat = 0;
}
