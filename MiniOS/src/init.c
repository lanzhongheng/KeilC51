
#include "../include/system.h"
#include "../include/macro.h"

void InitVars();
void InitTasks();

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

}
